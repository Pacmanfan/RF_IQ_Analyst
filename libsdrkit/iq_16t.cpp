#include "iq_16t.h"


IQ_16T_Writer::IQ_16T_Writer() : IQ_Writer(), SRIFile()
{
     m_conv_buff = 0;
     m_conv_buff_len = 0;
}

IQ_16T_Writer::~IQ_16T_Writer()
{
    if(m_conv_buff !=0)
    {
        delete []m_conv_buff;
    }
}


void IQ_16T_Writer::AddData(complex<float> *iq, unsigned int numsamples)
{
    if(numsamples > m_conv_buff_len)
    {
        //delete the old
        if(m_conv_buff !=0)
        {
            delete []m_conv_buff;
            m_conv_buff_len = 0;
        }
        // create a new
        m_conv_buff_len = numsamples * 2;
        m_conv_buff = new short [m_conv_buff_len];
    }

    //get a float pointer
    float *iqd = (float *)iq;
    short *outp = m_conv_buff;
    // iterate over the samples as floats
    for(unsigned int c = 0; c < numsamples * 2; c++)
    {
        float tmp = *iqd * 32768.0f;

        *outp = (short) tmp; // scale the (-1.. 1) float value into a short
        iqd++;
        outp++;
    }
    //write the data to the file
    fwrite(m_conv_buff,sizeof(short) * 2 * numsamples,1,fp);
}

bool IQ_16T_Writer::Setup(int streamid,double CF_Hz, double aSPS, double BW_Hz, double RFGain, double IFGain)
{
    UNUSED(streamid);
    CF = CF_Hz;
    BW = BW_Hz;
    SPS = aSPS;
    RefLevDB = 0;
    gain1 = RFGain;
    gain2 = IFGain;
    offset = 0;
    return true;
}

IQ_16T_Reader::IQ_16T_Reader()
{
    tbuf_s = 0;
    tbuf_f = 0;
    _sz = 0;
}

IQ_16T_Reader::~IQ_16T_Reader()
{
    tbuf_s = 0;
    tbuf_f = 0;
    _sz = 0;

}
void IQ_16T_Reader::Release()
{
    if(tbuf_f !=0 )
    {
        delete []tbuf_f;
    }
    if(tbuf_s !=0 )
    {
        delete []tbuf_s;
    }

    _sz = 0;
}

long IQ_16T_Reader::ReadSamples(CircBuff<complex<float> > *buffer,unsigned int numsamples)
{
    // re-allocate memeory if needed
    if(_sz < numsamples *2)
    {
        Release();
        tbuf_s = new short[ numsamples *2];
        tbuf_f = new float[ numsamples *2];
        _sz = numsamples;
    }
    //read samples from the file, pay attention to the number returned
    size_t numread = fread(tbuf_s,sizeof(short) *2,numsamples,fp);
    float *fdat = tbuf_f; // get a pointer to the float buffer
    short *sdat = tbuf_s; // and the short buffer
    //process a half sample at a time
    for(unsigned int c = 0; c < numread * 2; c++)
    {
        *fdat = ((float)*sdat) / 32768.0f;
        fdat++;
        sdat++;
    }
    // write the processed samples into the output buffer
    buffer->write((complex<float> *)tbuf_f,numread);
    return numread;
}
