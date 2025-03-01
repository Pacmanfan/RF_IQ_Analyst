#include <qvrt_tools.h>
using namespace std;

#define ROUGH_EST_SCALER .998

QVRT_FileInfo::QVRT_FileInfo()
{
    m_name = "";
    m_combined = false;

}

QVRT_FileInfo::~QVRT_FileInfo()
{
    Release();
}

void QVRT_FileInfo::Release()
{
    m_name = "";
    m_combined = false;

    for(unsigned int c = 0; c< m_streams.size(); c++)
    {
        StreamInfo *si = m_streams[c];
        delete si;
    }

    m_streams.clear();
}

/*
    Gather up information about all data streams
    -combined status
    -duration of streams
        time
        approx # samples

    so, when we encounter a datastream, we know that a context packet MUST appear at least once per second of data
*/
bool QVRT_FileInfo::GatherInfo(string filename)
{
    Release();
    m_name = filename;
    int MAX_DATA_TRY  = 100;
    int MAX_CTX_TRY  = 3;

    QVRT_Reader reader;
    if(!reader.Open(filename))
    {
        return false;
    }

    long filelen = reader.FileLength();

    QVRT_Header *header;
    QVRT_IFContext_Packet ifctx;
    QVRT_IQDataPacket datapacket;
    datapacket.m_numsamples = 0;

    unsigned char *data = nullptr;
    int ctxcnt = 0;
    int datacnt = 0;

    header = reader.ReadNextPacket();
    while(header != nullptr)
    {
        data = reader.CurrentBufferPos();
        switch(header->packetType)
        {
            case QVRT_IF_CONTEXT:
                ctxcnt++; // total number of context packets encountered
                ifctx.Decode(data);
                if(!HasStream(ifctx.StreamID))
                {
                    StreamInfo *si = new StreamInfo();
                    *si = ifctx;
                    si->name = filename;
                    m_streams.push_back(si);
                }

                break;
            case QVRT_IQ_DATA:
                datacnt++;
                datapacket.Decode(data,(CircBuff_No_lock<complex<float>> *)nullptr,999);
                StreamInfo *si = GetStreamInfo(datapacket.StreamID);
                if(si != nullptr)
                {
                    si->samples_per_packet = datapacket.m_numsamples; // just found out this can change
                }
        }
        header = reader.ReadNextPacket();
        //check for breakout conditions
        //exceeded counts:
        if(datacnt > MAX_DATA_TRY && ctxcnt > MAX_CTX_TRY)
        {
            break;
        }
    }

    //set up the combined flag:
    if(NumStreams() > 1)
    {
        StreamInfo *si1 = GetStreamInfoIndex(0);
        StreamInfo *si2 = GetStreamInfoIndex(1);
        if(si1->SampleRateHz == si1->SampleRateHz)
        {
            //same samplerates, looks to see if cf of one is offset +/- (.5 * Rate)
            double rate = si1->BandwidthHZ;
            if(si1->dRFReferenceFrequency - rate == si2->dRFReferenceFrequency)
                m_combined = true;
            if(si1->dRFReferenceFrequency + rate == si2->dRFReferenceFrequency)
                m_combined = true;
        }
    }

    if(NumStreams() > 1) // if we have both streams
    {
        StreamInfo *si1 = GetStreamInfoIndex(0);
        StreamInfo *si2 = GetStreamInfoIndex(1);

        //get the total rate
        double spstotal = si1->SampleRateHz + si2->SampleRateHz;
        double ratio1 = si1->SampleRateHz / spstotal;
        double ratio2 = si2->SampleRateHz / spstotal;
        double roughsamples = filelen / 4;
        //generate rough estimates of samples
        si1->num_samples_est = roughsamples * ratio1 * ROUGH_EST_SCALER;
        si2->num_samples_est = roughsamples * ratio2 * ROUGH_EST_SCALER;
        si1->duration_est_seconds = ((double)si1->num_samples_est) / si1->SampleRateHz;
        si2->duration_est_seconds = ((double)si2->num_samples_est) / si2->SampleRateHz;
    }
    else if (NumStreams() == 1 ) // just stream 1
    {
        StreamInfo *si1 = GetStreamInfoIndex(0);
        double roughsamples = filelen / 4;
        //generate rough estimates of samples
        si1->num_samples_est = roughsamples * ROUGH_EST_SCALER;
        si1->duration_est_seconds = ((double)si1->num_samples_est) / si1->SampleRateHz;
    }
    /*
    else if (_ctx2)// just stream 2
    {
        StreamInfo *si2 = GetStreamInfo(RADIO_B_STREAMID);
        double roughsamples = filelen / 4;
        //generate rough estimates of samples
        si2->num_samples_est = roughsamples * ROUGH_EST_SCALER;
        si2->duration_est = ((double)si2->num_samples_est) / si2->SampleRateHz;

    }
    */
    reader.Close();
    return true;

}
/*
    This is used to load up the meta-data for the file, Since it can take a
    few seconds to go through a qvrt file and determine streams, it is preferable to
    do this once and load and save the info through the use of auxillery meta files
*/
bool QVRT_FileInfo::LoadMeta(string filename)
{
    FILE *fp = fopen(filename.c_str(),"rb");
    if(!fp)
        return false;
    //read the number of streams
    int numstreams = m_streams.size();
    if(fread(&numstreams,sizeof(int),1,fp) !=1) return false;

    for(int c = 0; c < numstreams; c++)
    {
        StreamInfo *si = new StreamInfo();
        si->Load(fp);
        m_streams.push_back(si);
    }

    fclose(fp);
    return true;
}

bool QVRT_FileInfo::SaveMeta(string filename)
{
    FILE *fp = fopen(filename.c_str(),"wb");
    if(!fp)
        return false;
    //write the number of streams
    int numstreams = m_streams.size();
    fwrite(&numstreams,sizeof(int),1,fp);
    for(unsigned int c = 0; c < m_streams.size(); c++)
    {
        StreamInfo *si = m_streams[c];
        si->Save(fp);
    }

    fclose(fp);
    return true;
}

void QVRT_FileInfo::Dump()
{
    cout << "QVRT File Information ***************************\r\n";
    for(unsigned int c = 0; c < m_streams.size(); c++)
    {
        StreamInfo *si = m_streams[c];
        si->Dump();
    }
}

bool QVRT_FileInfo::HasStream(unsigned int streamid)
{
    return GetStreamInfo(streamid)?true:false;
}

StreamInfo *QVRT_FileInfo::GetStreamInfo(unsigned int streamid)
{
    for(unsigned int c = 0; c < m_streams.size(); c++)
    {
        StreamInfo *si = m_streams[c];
        if(si->StreamID == streamid)
            return si;
    }
    return nullptr;
}

StreamInfo *QVRT_FileInfo::GetStreamInfoIndex(unsigned int idx)
{
    StreamInfo *si = m_streams[idx];
    return si;
}


