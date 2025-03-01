
#include <qvrt_tools.h>
#define QVRT_OUT_BUFF_SIZE  1000000
#define NUM_IQ_DATA_PACKET 995
#define CTX_MODULUS 100
/*
This class is used to Write a QVRT Stream to file
This supports a single stream of data
*/
IQ_Writer::IQ_Writer()
{
    fp = 0;
    m_filename = "";
}

IQ_Writer::~IQ_Writer()
{

}

void IQ_Writer::AddData(complex<float> *iq, unsigned int numsamples)
{
    UNUSED(iq);
    UNUSED(numsamples);

}

bool IQ_Writer::Setup(int streamid,double CF_Hz, double SPS, double BW_Hz, double RFGain, double IFGain)
{
    UNUSED(streamid);
    UNUSED(CF_Hz);
    UNUSED(SPS);
    UNUSED(BW_Hz);
    UNUSED(RFGain);
    UNUSED(IFGain);
    return false;
}

void IQ_Writer::SetGPSData(double Latitude, double Longitude, double Altitude)
{
    UNUSED(Latitude);
    UNUSED(Longitude);
    UNUSED(Altitude);
}

bool IQ_Writer::Open(std::string filename)
{
    fp = fopen(filename.c_str(),"wb");
    if(!fp)
        return false;
    return true;
}

void IQ_Writer::Close()
{
    Flush();
    fclose(fp);
    fp =0;
}

bool IQ_Writer::IsOpen()
{
    if(fp != 0)
        return true;
    return false;
}

void IQ_Writer::Flush()
{

}

QVRT_Writer::QVRT_Writer() : IQ_Writer()
{
    m_samples = new CircBuff<float>(QVRT_OUT_BUFF_SIZE * 2);
    fp =0;
    m_packetcount = 0;
}

QVRT_Writer::~QVRT_Writer()
{
    delete m_samples;
}

void QVRT_Writer::PyAddData(long dataptr, uint32_t numsamples)
{
    complex<float> * data = (complex<float> *)dataptr;
    AddData(data,numsamples);
}

void QVRT_Writer::Flush()
{
    //there might be iq data packets remaining , up to 995....
    float tmpdata[995*2];
    static unsigned char dat[4000];
    QVRT_IQDataPacket datpack;
    if(m_samples->size() > 0)
    {
        memset(tmpdata,0,sizeof(NUM_IQ_DATA_PACKET*2));
        int num = (NUM_IQ_DATA_PACKET*2) - m_samples->size();
        m_samples->write(tmpdata,num); // fill it

        datpack.Encode(dat,m_samples);
        fwrite(dat,4000,1,fp);
        m_packetcount++;
        m_samples->clear();
    }
}

void QVRT_Writer::AddData(complex<float> *iq, unsigned int numsamples)
{
    static unsigned char dat[4000];

    QVRT_IQDataPacket datpack;
    //write new data into the buffer
    m_samples->write((float *)iq,numsamples*2);
    if(m_packetcount == 0)
    {
        //new file, write a context packet
        EncodeContextChunk(dat);
        fwrite(dat,4000,1,fp);
        m_packetcount++;
    }
    while (m_samples->size() >= (NUM_IQ_DATA_PACKET *2))
    {
        //m_ctx.Frac_Sec_TS += NUM_IQ_DATA_PACKET;
        datpack.Frac_Sec_TS += NUM_IQ_DATA_PACKET;
        datpack.Encode(dat,m_samples);
        fwrite(dat,4000,1,fp);
        m_packetcount++;
        //Add a context packet every 100 packets
        if(m_packetcount % CTX_MODULUS == 0)
        {
            EncodeContextChunk(dat);
            fwrite(dat,4000,1,fp);
            m_packetcount++;
        }
    }
}

bool QVRT_Writer::Setup(int streamid, double CF_Hz, double SPS, double BW_Hz, double RFGain, double IFGain)
{
    m_streamid = streamid;
    m_CF_Hz = CF_Hz;
    m_SPS = SPS;
    m_BW_Hz = BW_Hz;
    m_RFGain = RFGain;
    m_IFGain = IFGain;
    return true;
}

void QVRT_Writer::SetGPSData(double Latitude, double Longitude, double Altitude)
{
     m_ctx.Altitude = Altitude;
     m_ctx.Latitude = Latitude;
     m_ctx.Longitude = Longitude;
}



/* the Context area- which contains a 4000 byte block containing context data
 *(consisting of one Extension Data + one IF Context Packet).
 */
void QVRT_Writer::EncodeContextChunk(unsigned char * contextchunk)
{
    //for now, the span is equal to the bandwidth
    extpacket.m_tunerASettings.m_BandwidthHz = m_BW_Hz;
    extpacket.m_tunerASettings.m_Span =  m_SPS / 1000000.0f;// in Mhz
    extpacket.m_tunerASettings.m_centerFreq = m_CF_Hz / 1000000.0f; // in Mhz
    //make sure to set the correct stream id for the if context packet.
    extpacket.m_tunerBSettings.m_BandwidthHz = m_BW_Hz;
    extpacket.m_tunerBSettings.m_Span =  m_SPS / 1000000.0f;// in Mhz
    extpacket.m_tunerBSettings.m_centerFreq = m_CF_Hz / 1000000.0f; // in Mhz

    m_ctx.StreamID = m_streamid;
    if (m_streamid == 1)
    {
        extpacket.m_radioSelection = "Radio_A";

    }else if (m_streamid == 2)
    {
        extpacket.m_radioSelection = "Radio_B";
    }

    int len = extpacket.Encode(contextchunk);
    unsigned char * dat = contextchunk;
    dat += len;
    //now encode the if context packet.
    //flags to indicate change
    m_ctx.f_ContextFieldIndicatorChange = 1; //say it's changed
    m_ctx.f_ReferencePointIndicator = 1;
    m_ctx.f_Bandwidth = 1;
    m_ctx.f_RFReferenceFrequency = 1;
    m_ctx.f_ReferenceLevel = 1;
    m_ctx.f_Gain = 1;
    m_ctx.f_SampleRate = 1;
    m_ctx.f_TimestampCalibrationTime = 1;
    m_ctx.f_FormattedGPSGeolocation = 1;

    m_ctx.ReferencePointIndicator = 1;
    m_ctx.dBandwidth = m_BW_Hz;
    m_ctx.dRFReferenceFrequency = m_CF_Hz;
    m_ctx.dSampleRate = m_SPS;
    m_ctx.TimestampCalibrationTime = 0;
    m_ctx.TSI = 2;
    m_ctx.TSF = 2;
    m_ctx.GPS_INS_Manufacturer_OUI = 13945454;
    m_ctx.ISTSPF = 4294967295;
    m_ctx.FSTPF1 = 4294967295;
    m_ctx.FSTPF2 = 4294967295;
    /*
    m_ctx.Latitude = 0;
    m_ctx.Longitude = 0;
    m_ctx.Altitude = 0;
    */
    m_ctx.SpeedOverGround = 0;
    m_ctx.HeadingAngle = 0;
    m_ctx.TrackAngle = 0;
    m_ctx.MagneticVariation = 0;
    m_ctx.Encode(dat);
}
