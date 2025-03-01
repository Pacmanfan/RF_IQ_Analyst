#include "sampleindexer.h"
#include <qvrt_tools.h>
#include <stdio.h>
#include <fft_hist.h>
#include <stdio.h>
#include <QFileInfo>
#include <QDir>
#include <utils.h>
#include <iq_u8.h>
#include <iq_32.h>

void *buildindexthread(void *param);
//string myfn;

#define DUMMYSIZE 100000
#define CFBUFFSIZE (70000)


SampleIndexer::SampleIndexer(QObject *parent)
    :QObject(parent)
{
    //start off with a little storage
    m_samp_idxs.clear(); // an array of sampleidx
    samplesout = new CircBuff<complex<float> >(CFBUFFSIZE);
    m_si = nullptr;
    m_reader = 0;
}

SampleIndexer::~SampleIndexer()
{
    delete samplesout;
}

int SampleIndexer::streamid() const
{
    return m_si->StreamID;
}

void SampleIndexer::setStreamid(int streamid)
{
    m_si->StreamID = streamid;
}

bool SampleIndexer::PastLength(uint64_t sampleindex)
{
    if(sampleindex > m_samp_idxs[m_samp_idxs.size() - 1]->m_abs_sample_idx)
        return true;
    return false;
}


void SampleIndexer::StartThreadedBuildIndexTable(StreamInfo *si)
{
    m_si = si;
    //pthread_create(&bit, NULL, buildindexthread, this);
    bit = new std::thread([this]{BuildIndexTable();});
}

/*
This call opens a handle to the actual QVRT/16T/s16/u8 file
*/
bool SampleIndexer::Open()
{
    if(m_reader != nullptr) // close and delete first if open
    {
        if(m_reader->IsOpen())
            m_reader->Close();
        delete m_reader;
        m_reader = nullptr;
    }

    IQ_U8_Reader *u8rd =  nullptr;
    IQ_16T_Reader *s16rd = nullptr;
    IQ_32_Reader *iq32rd = nullptr;

    QVRT_Reader *rd =nullptr;
    switch(m_si->m_format)
    {
        case eU8:
            u8rd =  new IQ_U8_Reader();
            m_reader = (IQ_Reader *)u8rd;
            if(!u8rd->Open(m_si->name)) // open the IQ portion
            {
                delete u8rd;
                m_reader = nullptr;
                return false;
            }
        break;
    case eS8:
    break;
    case eU16:
    break;
    case eS16:
        s16rd =  new IQ_16T_Reader();
        m_reader = (IQ_Reader *)s16rd;
        if(!s16rd->Open(m_si->name)) // open the IQ portion
        {
            delete s16rd;
            m_reader = nullptr;
            return false;
        }
    break;
    case e32:
        iq32rd = new IQ_32_Reader();
        m_reader = (IQ_Reader *)iq32rd;
        if(!iq32rd->Open(m_si->name)) // open the IQ portion
        {
            delete iq32rd;
            m_reader = nullptr;
            return false;
        }

    break;
    case eQVRT:
        rd = new QVRT_Reader();
        m_reader = (IQ_Reader *)rd;
        if(!m_reader->Open(m_si->name))
        {
            printf("Could not open file %s\r\n",m_si->name.c_str());
            return false;
        }

        break;
    case eUNK:
    break;
    }

    return true;
}

void SampleIndexer::Close()
{
    if(m_reader != nullptr)
    {
        if(m_reader->IsOpen())
            m_reader->Close();

    }
}

bool SampleIndexer::IsOpen()
{
    if(m_reader != nullptr)
        return m_reader->IsOpen();
    return false;
}


/*
This is going to have to change because the samples per packet in each IF data packet can change during the stream
*/
bool SampleIndexer::BuildIndexTable()
{
    QVRT_Reader reader;
    for(unsigned int c = 0; c < m_samp_idxs.size(); c++)
    {
        sample_idx *idx = m_samp_idxs[c];
        delete idx;
    }
    m_samp_idxs.clear();
    QVRT_Header *header;
    QVRT_IQDataPacket datapacket;

    // if this is a 16T file, simply say we're done
    QFileInfo fi(m_si->name.c_str());
    //file_format fmt = DetermineFormat(fn.c_str());

    if(m_si->m_format != eQVRT)
    {
        // not a qvrt file
        // no need to go further
        emit EndBuildIndex();
        return true;
    }

    if(!reader.Open(m_si->name))
    {
        printf("Could not open file %s\r\n",m_si->name.c_str());
        return false;
    }

    //check and see if the index file already exists, if so, load it.
    // use the streamid
    QString snum = QString::number(m_si->StreamID);
    QString fidxname = fi.absolutePath() + "/" + fi.baseName() +"_" + snum + ".idx";

    QFileInfo check_file(fidxname);

    if(check_file.exists())
    {
        if(Load(fidxname))
        {
            emit EndBuildIndex();
            return true;
        }
    }

    emit StartBuildIndex();
    unsigned char *data;
    long curpos = 0;
    header = reader.ReadNextPacket();
    uint64_t sampidx = 0;
    while (header != 0)
    {
        data = reader.CurrentBufferPos();
        switch(header->packetType)
        {
            case QVRT_IQ_DATA:

                datapacket.Decode(data,(CircBuff_No_lock<complex<float>> *)0,999);
                if(datapacket.StreamID == m_si->StreamID)
                {
                    //save the current index
                    //m_indexes.push_back(curpos);
                    sample_idx *si = new sample_idx;
                    si->m_filepos = curpos;
                    si->m_abs_sample_idx = sampidx;
                    m_samp_idxs.push_back(si);
                    //increment the number of samples AFTER we set this sampleidx up
                    sampidx += datapacket.m_numsamples;

                }
                break;
            default:
                break;

        }
        curpos = reader.TellP(); // the current position in the file
        header = reader.ReadNextPacket();
    }
    reader.Close();
    Save(fidxname);// save the index file for later
    emit EndBuildIndex();
    return true;
}

double SampleIndexer::CF_Hz()
{
    return m_si->CenterFreqHz;
}

double SampleIndexer::BW_Hz()
{
    return m_si->BandwidthHZ;
}

/*
This function calculates the fileposition for any given sample index
*/
/*

so, if we're looking for sample index 2000
we iterate until we go past it,
[0,0] // file pos 0, samples up to this point = 0
[x,0] // file pos x, samples up to this point = 995
[y,0] // file pos y, samples up to this point = 1990
[z,0] // file pos z, samples up to this point = 2985

then, go back 1 item
reminder is the m_abs_sample_idx - sampleindex

*/
long SampleIndexer::Index(uint64_t sampleindex, int *premainder)
{
    long fidx = -1; // the file position in bytes is what we're returning so the caller can perform a seek
    // find the item that is previous to the index we're looking for

    for(unsigned int c = 0; c < m_samp_idxs.size();c++)
    {
        //check to see if we just past it
        if(m_samp_idxs[c]->m_abs_sample_idx > sampleindex )
        {
            int idx = c - 1;// go back 1
            if(idx >= 0)
            {
                fidx = m_samp_idxs[idx]->m_filepos;
                //now calculate remainder
                *premainder = sampleindex - m_samp_idxs[idx]->m_abs_sample_idx;
                if(*premainder < 0)
                    *premainder = 0;
                break;
            }else
            {
                break;
            }
        }
    }
    if(fidx == -1)
        fidx = -1;
    return fidx;
}


void SampleIndexer::GetSamples(long sampleidx, int numsamples, complex<float> *IQData)
{
    if(!IsOpen())
        return;

    static complex<float> dummy[DUMMYSIZE];
    long fidx = 0; // file index
    int premainder = 0; //
    if(m_si->m_format == eQVRT)
    {
        fidx = Index(sampleidx,&premainder);
        QVRT_Reader *rd = (QVRT_Reader *)m_reader;
        rd->setStreamid(m_si->StreamID); // make sure to set the stream identifier

    }else if(m_si->m_format == eS16 || m_si->m_format == eU16)
    {
        fidx = sampleidx * 4; // 2 bytes for I and 2 for Q
    }else if (m_si->m_format == eU8 || m_si->m_format == eS8)
    {
        fidx = sampleidx * 2; // 1 byte for I and 1 for Q
    }else if (m_si->m_format == e32)
    {
        fidx = sampleidx * 8; // 4 bytes for I and 1 for Q
    }
    m_reader->SeekP(fidx); // go to the right spot in the file
    m_reader->ReadSamples(samplesout,numsamples + premainder); // read the samples - may return more than asked

    if(premainder > 0)
    {
        samplesout->read(dummy,premainder); // eat some samples
    }
    samplesout->read(IQData,numsamples);
    samplesout->clear(); // discard any remainder
}

/*
Basic load and save functionality for the index files
*/
bool SampleIndexer::Save(QString filename)
{
    FILE *fp = fopen(filename.toLatin1().data(),"wb");
    if(!fp)
        return false;
    long sz = m_samp_idxs.size();
    fwrite(&sz,sizeof(long),1,fp);
    for(long cnt = 0; cnt < sz; cnt ++)
    {
        sample_idx *si = m_samp_idxs[cnt];
        fwrite(&si->m_filepos,sizeof(uint64_t),1,fp);
        fwrite(&si->m_abs_sample_idx,sizeof(uint64_t),1,fp);
    }
    fclose(fp);
    return true;
}

bool SampleIndexer::Load(QString filename)
{
    FILE *fp = fopen(filename.toLatin1().data(),"rb");
    if(!fp)
        return false; // can't open / doesn't exist

    //delete and remove previous entries
    for(unsigned int c =0 ; c < m_samp_idxs.size(); c++)
    {
        sample_idx *si  = m_samp_idxs[c];
        delete si;
    }

    m_samp_idxs.clear();

    long numread = 0;
    long szA = 0;
    numread = fread(&szA,sizeof(long),1,fp);
    if(numread != 1)
        return false;

    m_samp_idxs.reserve(szA);
    for(int cnt = 0; cnt < szA; cnt ++)
    {
        sample_idx *si = new sample_idx;
        fread(&si->m_filepos,sizeof(uint64_t),1,fp);
        fread(&si->m_abs_sample_idx,sizeof(uint64_t),1,fp);
        m_samp_idxs.push_back(si);
    }

    fclose(fp);
    return true;
}

