#include "data_exporter.h"
#include <cnpy.h>
#include <QFileInfo>

using namespace cnpy;

void *exportthreadfn(void *param);
#define EXPORT_NPY_SIZE 64000


void gen_random(char *s, const int len)
{
    for (int i = 0; i < len; ++i)
    {
        int randomChar = rand()%(26+26+10);
        if (randomChar < 26)
            s[i] = 'a' + randomChar;
        else if (randomChar < 26+26)
            s[i] = 'A' + randomChar - 26;
        else
            s[i] = '0' + randomChar - 26 - 26;
    }
    s[len] = 0;
}

std::string GenerateExportName()
{
    char temp[20];
 // samples-adrzlfulkugjfmla.npy
    std::string retstr = "";
    gen_random(temp,16);
    retstr += "samples-";
    retstr += temp;
    retstr += ".npy";
    return retstr;
}

data_exporter::data_exporter(QObject *parent) : QObject(parent)
{

}

void data_exporter::StartExporting(QVRT_FileInfo *fi, ftmarker *ftm, QString inputfilenme, QString outputbasename, int StreamID, double bandwidthHz)
{

    m_fi = fi;
    infile = inputfilenme;
    outfile = outputbasename;
    m_format_in = DetermineFormat(inputfilenme);
    m_bandwidthHz = bandwidthHz;
    m_marker = ftm;
    m_streamid = StreamID;
    //pthread_create(&rst, NULL, exportthreadfn, this);
    rst = new std::thread([this]{DoExport();});
}

void data_exporter::DoExport()
{
    resampler_arb rsmp;
    IQ_Reader *m_reader;

    srand(time(NULL));
    //set up the reader
    if(m_format_in == eQVRT)
    {
        m_reader = new QVRT_Reader();
    }else if (m_format_in == eS16)
    {
        m_reader = new IQ_16T_Reader();
    }

    string fn = infile.toLatin1().data();
    StreamInfo si;

    std::complex<float> indata[EXPORT_NPY_SIZE];
    std::complex<float> sindata[EXPORT_NPY_SIZE]; // temporary buffer
    std::complex<float> outdata[EXPORT_NPY_SIZE];
    CircBuff<complex<float> > *iqdata = new CircBuff<complex<float>>(1000000);
    CircBuff<complex<float> > *iqoutdata = new CircBuff<complex<float>>(1000000);

    //get infor about the source stream
    if(m_format_in == eQVRT)
    {
        if(m_fi->HasStream(m_streamid))
        {
            si = *m_fi->GetStreamInfo(m_streamid);
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

    long startidx = m_marker->StartTime_S() * si.SampleRateHz; // time in seconds
    long endindex = m_marker->EndTime_S() * si.SampleRateHz; // time in seconds

    long cursampidx = 0; // the current sample index we're on

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

    //set up the resampler
    rsmp.set_attenuation(60);
    double filterwidth  = (m_marker->BW_Hz()) / si.SampleRateHz;
    double resamplerate  = m_bandwidthHz  / si.SampleRateHz;
    rsmp.set_rate(resamplerate);
    rsmp.set_filter_width(filterwidth/2.0);

    // set up the signal source for offset tuning
    sigsrc_resamp.set_sampling_freq(si.SampleRateHz);
    sigsrc_resamp.set_amplitude(1);
    double freqdiff = (si.CenterFreqHz - (m_marker->CF_Hz()));// / si.BandwidthHZ;
    sigsrc_resamp.set_frequency(freqdiff);

    emit(StartExport(m_marker));
    m_running = true;
    while(m_running)
    {
        size_t numread = m_reader->ReadSamples(iqdata,EXPORT_NPY_SIZE);
        if(numread == 0)
            break; // no more samples
        //get data from the circ buffer
        iqdata->read(indata,numread);
        cursampidx += numread;

        //shift the data by the correct frequency
        sigsrc_resamp.work(numread,sindata);
        for(unsigned int c = 0 ; c < numread; c++)
            indata[c] *= sindata[c];

        //resample the data
        unsigned int outcnt;// = floor(((float)numread) * filterwidth);
        rsmp.resample(indata,outdata,numread, &outcnt);
        //write it back out
        //now, copy into a circular buffer so we can retrieve exactly  EXPORT_NPY_SIZE samples
        iqoutdata->write(outdata,outcnt);


        while(iqoutdata->size() > EXPORT_NPY_SIZE)
        {
            // get exactly EXPORT_NPY_SIZE samples
            //re-use outdata array (don't get confused...)
            //now write a complete numpy file
            iqoutdata->read(outdata,EXPORT_NPY_SIZE);
            //int16_t i16[EXPORT_NPY_SIZE];
            complex<double> cdIQ[EXPORT_NPY_SIZE];
           // char *tiq = (char *)&i16[0];
            double *dp = (double *)cdIQ;
            float *fiq = (float *)outdata;
            for(unsigned int c = 0 ; c< EXPORT_NPY_SIZE ; c++)
            {
                //I data
                *dp = *fiq;
                dp++;
                fiq++;
                //Q data
                *dp = *fiq;
                dp++;
                fiq++;
            }
            //now write it out...
            std::string fname = outfile.toLatin1().data();
            fname += GenerateExportName();
            npy_save(fname,cdIQ,{64000});
        }

        emit(ProgressExport()); // save we saved one


        if(cursampidx >= endindex && m_marker->HasEndTime() == true)
        {
            m_running = false;
        }
    }

    m_reader->Close();
    delete m_reader;
    delete iqdata;
    delete iqoutdata;
    emit(EndExport());
}

/*
This is the same as above, but it only exports a single file. It's also a syncronous call
*/
void data_exporter::SingleExport(QVRT_FileInfo *fi, ftmarker *ftm,QString inputfilenme, QString outfilename, int StreamID, double bandwidthHz)
{
    srand(time(NULL));
    m_fi = fi;
    infile = inputfilenme;
    outfile = outfilename;
    m_format_in = DetermineFormat(inputfilenme);
    m_bandwidthHz = bandwidthHz;
    m_marker = ftm;
    m_streamid = StreamID;

    resampler_arb rsmp;
    IQ_Reader *m_reader;


    //set up the reader
    if(m_format_in == eQVRT)
    {
        m_reader = new QVRT_Reader();
    }else if (m_format_in == eS16)
    {
        m_reader = new IQ_16T_Reader();
    }

    string fn = infile.toLatin1().data();
    StreamInfo si;

    std::complex<float> indata[EXPORT_NPY_SIZE];
    std::complex<float> sindata[EXPORT_NPY_SIZE]; // temporary buffer
    std::complex<float> outdata[EXPORT_NPY_SIZE];
    CircBuff<complex<float> > *iqdata = new CircBuff<complex<float>>(1000000);
    CircBuff<complex<float> > *iqoutdata = new CircBuff<complex<float>>(1000000);

    //get infor about the source stream
    if(m_format_in == eQVRT)
    {
        if(m_fi->HasStream(m_streamid))
        {
            si = *m_fi->GetStreamInfo(m_streamid);
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

    long startidx = m_marker->StartTime_S() * si.SampleRateHz; // time in seconds
    long endindex = m_marker->EndTime_S() * si.SampleRateHz; // time in seconds

    long cursampidx = 0; // the current sample index we're on

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
            QString fidxname = fi.absolutePath() + "/" + fi.baseName() + ".idx";
            indexer->Load(fidxname);
            int remainder = 0;
            fidx =  indexer->Index(startidx,&remainder);
            delete indexer;
        }else if (m_format_in == eS16)
        {
            fidx = startidx * 4; // 2 bytes for I and 2 for Q - calculated directly
        }
        m_reader->SeekP(fidx);
    }

    //set up the resampler
    rsmp.set_attenuation(60);
    double filterwidth  = (m_marker->BW_Hz()) / si.SampleRateHz;
    double resamplerate  = m_bandwidthHz  / si.SampleRateHz;
    rsmp.set_rate(resamplerate);
    rsmp.set_filter_width(filterwidth/2.0);

    // set up the signal source for offset tuning
    sigsrc_resamp.set_sampling_freq(si.SampleRateHz);
    sigsrc_resamp.set_amplitude(1);
    double freqdiff = (si.CenterFreqHz - (m_marker->CF_Hz()));// / si.BandwidthHZ;
    sigsrc_resamp.set_frequency(freqdiff);

    emit(StartExport(m_marker));
    m_running = true;
    while(m_running)
    {
        size_t numread = m_reader->ReadSamples(iqdata,EXPORT_NPY_SIZE);
        if(numread == 0)
            break; // no more samples
        //get data from the circ buffer
        iqdata->read(indata,numread);
        cursampidx += numread;

        //shift the data by the correct frequency
        sigsrc_resamp.work(numread,sindata);
        for(unsigned int c = 0 ; c < numread; c++)
            indata[c] *= sindata[c];

        //resample the data
        unsigned int outcnt;// = floor(((float)numread) * filterwidth);
        rsmp.resample(indata,outdata,numread, &outcnt);
        //write it back out
        //now, copy into a circular buffer so we can retrieve exactly  EXPORT_NPY_SIZE samples
        iqoutdata->write(outdata,outcnt);


        if(iqoutdata->size() > EXPORT_NPY_SIZE)
        {
            // get exactly EXPORT_NPY_SIZE samples
            //re-use outdata array (don't get confused...)
            //now write a complete numpy file
            iqoutdata->read(outdata,EXPORT_NPY_SIZE);
            //int16_t i16[EXPORT_NPY_SIZE];
            complex<double> cdIQ[EXPORT_NPY_SIZE];
           // char *tiq = (char *)&i16[0];
            double *dp = (double *)cdIQ;
            float *fiq = (float *)outdata;
            for(unsigned int c = 0 ; c< EXPORT_NPY_SIZE ; c++)
            {
                //I data
                *dp = *fiq;
                dp++;
                fiq++;
                //Q data
                *dp = *fiq;
                dp++;
                fiq++;
            }
            //now write it out...
            std::string fname = outfile.toLatin1().data();

            npy_save(fname,cdIQ,{64000});
            break; // time to go..
        }

        if(cursampidx >= endindex && m_marker->HasEndTime() == true)
        {
            m_running = false;
        }
    }

    m_reader->Close();
    delete m_reader;
    delete iqdata;
    delete iqoutdata;
}
