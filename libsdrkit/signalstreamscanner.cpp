#include "signalstreamscanner.h"
#include <QFileInfo>
#include <sampleindexer.h>
#include <fft_fftw.h>
#include <feature_detector.h>

extern file_format DetermineFormat(QString filename);
#define SEARCH_IQ_BUFFER_SIZE 32768

SignalStreamScanner::SignalStreamScanner(QObject *parent) : QObject(parent)
{
     m_running = false;
     m_fft_hist = new FFT_Hist();
}

void SignalStreamScanner::StartDetecting(ftmarker *ftm,QString inputfilenme, int StreamID, size_t fft_search_size, size_t fft_interleave)
{
    infile = inputfilenme;
    m_format_in = DetermineFormat(inputfilenme);
    m_marker = ftm;
    m_streamid = StreamID;
    m_fft_search_size = fft_search_size;
    m_fft_interleave = fft_interleave;
    m_running = false;
    //pthread_create(&rst, nullptr, scanthreadfn, this);
    rst = new std::thread([this]{ScanThread();});
}
/*
We're going to use the feature detector in chunks
we should have some measure of overlap as well
*/
void SignalStreamScanner::ScanThread()
{
    IQ_Reader *m_reader = nullptr;
    feature_detector detector;
    QVector<ftmarker *> markers;
   // int overlap = 10; //10 rows overlap
    if(m_format_in == eQVRT)
    {
        m_reader = new QVRT_Reader();
    }else if (m_format_in == eS16)
    {
        m_reader = new IQ_16T_Reader();
    }

    string fn = infile.toLatin1().data();
    StreamInfo si;

    //get infor about the source stream
    if(m_format_in == eQVRT)
    {
        QVRT_FileInfo fi;
        if(!fi.GatherInfo(infile.toLatin1().data()))
        {
            CancelDetecting();
            if(m_reader !=nullptr )
                delete m_reader;
            m_reader = nullptr;
            return;
        }
        if(fi.HasStream(m_streamid))
        {
            si = *fi.GetStreamInfo(m_streamid);
        }
    }else if (m_format_in == eS16)
    {
        //read the sri file for info
        IQ_16T_Reader *trd = (IQ_16T_Reader *)m_reader;
        QFileInfo fi(infile);
        QString sriname = fi.absolutePath() + "/" + fi.baseName() + ".sri";
        trd->Load(sriname);
        si.SampleRateHz = trd->SPS; // I think we just need the sample rate
        si.CenterFreqHz = trd->CF;
        si.BandwidthHZ = trd->BW;
    }
    //open an IQ file reader (QVRT or 16T)
    bool opened = m_reader->Open(fn);

    if(!opened)
    {
        return;
    }

    if(m_format_in == eQVRT)
    {
        //qvrt file readers need to set the stream id
        QVRT_Reader *tmpreader = (QVRT_Reader *)m_reader;
        tmpreader->setStreamid(m_streamid);
    }

    long startidx;
    long endindex;
    if(m_marker->HasStartTime())
    {
        startidx = m_marker->StartTime_S() * si.SampleRateHz; // time in seconds
    }

    if(m_marker->HasEndTime())
    {
        endindex = m_marker->EndTime_S() * si.SampleRateHz; // time in seconds
    }else
    {
        endindex = si.duration_est_seconds * si.SampleRateHz;
    }

    long cursampidx = 0; // the current sample index we're on

    if(m_marker->HasStartTime())
    {
        //start at the startidx in the source file
        cursampidx = startidx;
        long fidx = 0;
        if(m_format_in == eQVRT)
        {
            SampleIndexer *indexer = new SampleIndexer(nullptr);
            indexer->setStreamid(m_streamid);
            QFileInfo fi(infile);
            //we're using the sample indexer and the assumption that an index file exists
            QString fidxname = fi.absolutePath() + "/" + fi.baseName() + ".idx";
            indexer->Load(fidxname);
            int remainder = 0;
            fidx =  indexer->Index( startidx,&remainder);
            delete indexer;
        }else if (m_format_in == eS16)
        {
            fidx = startidx * 4; // 2 bytes for I and 2 for Q - calculated directly
        }
        m_reader->SeekP(fidx);
    }

    std::complex<float> indata[1000000];
    float fftdata[1000000];
    //std::complex<float> indata[m_fft_search_size];
    //float fftdata[m_fft_search_size];
    CircBuff<complex<float> > *iqdata = new CircBuff<complex<float>>(100000);

    m_running = true;

    fft_fftw fftcalc;

    float percent = 0;
    int rowcount =0; //to see if we have enough rows to process this yet.
    double rowsamplidx = 0;
    double block_start_time = 0;
    double time_per_sample_S = 1/si.SampleRateHz;
    while(m_running)
    {
        size_t numread = 0;
        //read data from the file stream
        // this is returning more data than what we need.
        if(iqdata->size() < m_fft_search_size + m_fft_interleave)
        {
            numread = m_reader->ReadSamples(iqdata,m_fft_search_size + m_fft_interleave);
            if(numread == 0 || (numread < m_fft_search_size + m_fft_interleave))
                break; // no more samples, end if file
            cursampidx += numread; // keep track of where we are in the file
        }
        //get iq data from the circular buffer to perform the fft
        iqdata->read(indata,m_fft_search_size);
        iqdata->skip(m_fft_interleave); // skip over the specified fft interval;

        //perform the fft
        fftcalc.PerformFFT(indata,fftdata,m_fft_search_size);
        //add the fft data to out fft_hist to get averages, time smoothing, etc..
        m_fft_hist->AddData(fftdata,m_fft_search_size,si.CenterFreqHz,si.BandwidthHZ);
        //rowcount++; // we added a row to the fft data
        //check and see if we have a full page of data yet

        if(rowcount++ >= m_fft_hist->MaxRows() )
        {
            double S_Per_Line = (m_fft_search_size + m_fft_interleave) * time_per_sample_S;// time per line
            markers = detector.DetectFeatures2(m_fft_hist,11,eRaw,false,S_Per_Line);
            //now, adjust the time and add to main marker set.
            for(int c = 0; c< markers.size(); c++)
            {
                ftmarker* ftm = markers.at(c);
                ftm->setStartTime_S(ftm->StartTime_S() + block_start_time );
                ftm->setEndTime_S(ftm->EndTime_S() + block_start_time);
            }
            m_markers.append(markers); //add the to the main set
            markers.clear(); // celar them out for next time
            rowcount = 0;
            block_start_time = rowsamplidx * time_per_sample_S;// mark the start time for the next block;
        }
        percent = ((double)rowsamplidx / (double)endindex) * 100;
        emit(Progress("",percent)); //
        rowsamplidx += m_fft_search_size + m_fft_interleave;

        if(rowsamplidx >= endindex && m_marker->HasEndTime() == true)
        {
            m_running = false;
        }
    }

    m_reader->Close();
    delete m_reader;
    delete iqdata;
    emit(Completed(false));
}

void SignalStreamScanner::CancelDetecting()
{
    m_running = false;
    emit(Completed(true));
}
