#include "file_resampler.h"
#include <qvrt_tools.h>
#include <string>
#include <resampler_arb.h>
#include <sampleindexer.h>
#include <QFileInfo>
#include <iq_16t.h>

#define RESAMPLE_SIZE 30000 // resample 30k samples at a time

void *resamplethreadfn(void *param);

file_resampler::file_resampler(QObject *parent) : QObject(parent)
{
    m_running = false;
    rst = nullptr;
}


void file_resampler::StartResampling(QVRT_FileInfo *fi, ftmarker *ftm,QString inputfilename, QString outputfilename, int streamid)
{
    m_fi = fi;
    infile = inputfilename;
    outfile = outputfilename;
    m_format_in = DetermineFormat(inputfilename);
    m_format_out = DetermineFormat(outputfilename);
    m_marker = ftm;
    m_streamid = streamid;
    rst = new std::thread([this]{DoResample();});
    //pthread_create(&rst, NULL, resamplethreadfn, this);
}



void file_resampler::DoResample()
{
    resampler_arb rsmp;
    IQ_Reader *m_reader;
    IQ_Writer *m_writer;

    //set up the reader
    if(m_format_in == eQVRT)
    {
        m_reader = new QVRT_Reader();
    }else if (m_format_in == eS16)
    {
        m_reader = new IQ_16T_Reader();
    }
    //set up the writer
    if(m_format_out == eQVRT)
    {
        m_writer = new QVRT_Writer();
    }else if (m_format_out == eS16)
    {
        m_writer = new IQ_16T_Writer();
    }

    string fn = infile.toLatin1().data();
    StreamInfo si;

    std::complex<float> indata[RESAMPLE_SIZE*2];
    std::complex<float> sindata[RESAMPLE_SIZE*2]; // temporary buffer
    std::complex<float> outdata[RESAMPLE_SIZE*2];
    CircBuff<complex<float> > *iqdata = new CircBuff<complex<float> >(1000000);

    //bool streampresent = false;
    //get infor about the source stream
    if(m_format_in == eQVRT)
    {
        if(m_fi->HasStream(m_streamid))
        {
            si = *m_fi->GetStreamInfo(m_streamid);
          //  streampresent = true;
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
       // streampresent = false;
    }
    //open an IQ file reader (QVRT or 16T)
    bool opened = m_reader->Open(fn);

    if(m_format_in == eQVRT)
    {
        //qvrt file readers need to set the stream id
        QVRT_Reader *tmpreader = (QVRT_Reader *)m_reader;
        tmpreader->setStreamid(m_streamid);
    }

    long startidx = m_marker->StartTime_S() * si.SampleRateHz; // time in seconds
    long endindex = m_marker->EndTime_S() * si.SampleRateHz; // time in seconds

    long cursampidx = 0; // the current sample index we're on

    bool outopend = m_writer->Open(outfile.toLatin1().data());

    if(!(opened &&  outopend))
    {
        emit(EndResample());
        delete m_reader;
        delete m_writer;
        return;
    }

    if(m_marker->HasStartTime())
    {
        //start at the startidx in the source file
        cursampidx = startidx;
        long fidx = 0;
        if(m_format_in == eQVRT)
        {
            SampleIndexer *indexer = new SampleIndexer(0);
            indexer->setStreamid(m_streamid);
            QFileInfo fi(infile);
            //we're using the sample indexer and the assumption that an index file exists
            //QString fidxname = fi.absolutePath() + "/" + fi.baseName() + ".idx";
            QString snum = QString::number(m_streamid);
            QString fidxname = fi.absolutePath() + "/" + fi.baseName() +"_" + snum + ".idx";

            if(!indexer->Load(fidxname))
            {
                return;
            }
            int remainder = 0;
            fidx =  indexer->Index(startidx,&remainder);
            delete indexer;
        }else if (m_format_in == eS16)
        {
            fidx = startidx * 4; // 2 bytes for I and 2 for Q - calculated directly
        }
        m_reader->SeekP(fidx);
    }

    //set up the output
    m_writer->Setup(m_streamid,m_marker->CF_Hz(),m_marker->BW_Hz(),m_marker->BW_Hz(),0,0);
    if(m_format_out == eS16)
    {
        //save the sri file
        QFileInfo fi(outfile);
        QString sriname = fi.absolutePath() + "/" + fi.baseName() + ".sri";
        // cast a temp pointer to access the member function
        IQ_16T_Writer *twriter = (IQ_16T_Writer *)m_writer;
        twriter->Save(sriname);
    }

    //set up the resampler
    rsmp.set_attenuation(60);
    double rate  = (m_marker->BW_Hz() ) / si.SampleRateHz;
    rsmp.set_rate(rate);
    rsmp.set_filter_width(rate/2.0);

    // set up the signal source for offset tuning
    sigsrc_resamp.set_sampling_freq(si.SampleRateHz);
    sigsrc_resamp.set_amplitude(1);
    double freqdiff = (si.CenterFreqHz - (m_marker->CF_Hz()));// / si.BandwidthHZ;
    sigsrc_resamp.set_frequency(freqdiff);

    emit(StartResample());
    m_running = true;
    while(m_running)
    {
        size_t numread = m_reader->ReadSamples(iqdata,RESAMPLE_SIZE);
        if(numread == 0)break; // no more samples
        //get data from the circ buffer
        iqdata->read(indata,numread);
        cursampidx += numread;

        //shift the data by the correct frequency
        sigsrc_resamp.work(numread,sindata);
        for(unsigned int c = 0 ; c < numread; c++)
            indata[c] *= sindata[c];

        //resample the data
        unsigned int outcnt;// = floor(((float)numread) * rate);
        rsmp.resample(indata,outdata,numread,&outcnt);
        //write it back out
        m_writer->AddData(outdata,outcnt);
        emit(ProgressResample());

        if(cursampidx >= endindex && m_marker->HasEndTime() == true)
        {
            m_running = false;
        }
    }

    m_reader->Close();
    m_writer->Close();
    delete m_reader;
    delete m_writer;
    delete iqdata;
    emit(EndResample());
}


