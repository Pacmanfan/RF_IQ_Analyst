#include "iq_u8.h"


IQ_U8_Writer::IQ_U8_Writer() : IQ_Writer(), SRIFile()
{
     m_conv_buff = 0;
     m_conv_buff_len = 0;
}

IQ_U8_Writer::~IQ_U8_Writer()
{
    if(m_conv_buff !=0)
    {
        delete []m_conv_buff;
    }
}

void IQ_U8_Writer::AddData(complex<float> *iq, unsigned int numsamples)
{
    if(numsamples > m_conv_buff_len)
    {
        //delete the old
        if(m_conv_buff !=nullptr)
        {
            delete []m_conv_buff;
            m_conv_buff_len = 0;
        }
        // create a new
        m_conv_buff_len = numsamples * 2;
        m_conv_buff = new uint8_t [m_conv_buff_len];
    }

    //get a float pointer
    float *iqd = (float *)iq;
    uint8_t *outp = m_conv_buff;
    // iterate over the samples as floats and convert them to unsigned 8 bit values
    for(unsigned int c = 0; c < numsamples * 2; c++)
    {
        float tmp = *iqd * 127.5f;
        *outp = (uint8_t)( tmp + 127.5); // scale the (-1.. 1) float value into an 8 bit unsigned int from 0-255 (127.5 is centerline)
        iqd++;
        outp++;
    }
    //write the data to the file
    fwrite(m_conv_buff,sizeof(short) * 2 * numsamples,1,fp);
}

bool IQ_U8_Writer::Setup(int streamid,double CF_Hz, double aSPS, double BW_Hz, double RFGain, double IFGain)
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

IQ_U8_Reader::IQ_U8_Reader()
{
    tbuf_u8 = 0;
    tbuf_f = 0;
}

IQ_U8_Reader::~IQ_U8_Reader()
{
    tbuf_u8 = 0;
    tbuf_f = 0;
    _sz = 0;

}
void IQ_U8_Reader::Release()
{
    if(tbuf_f !=0 )
    {
        delete []tbuf_f;
    }
    if(tbuf_u8 !=0 )
    {
        delete []tbuf_u8;
    }

    _sz = 0;
}

long IQ_U8_Reader::ReadSamples(CircBuff<complex<float> > *buffer,unsigned int numsamples)
{
    // re-allocate memeory if needed
    if(_sz < numsamples *2)
    {
        Release();
        tbuf_u8 = new uint8_t[ numsamples *2];
        tbuf_f = new float[ numsamples *2];
        _sz = numsamples;
    }
    //read samples from the file, pay attention to the number returned
    size_t numread = fread(tbuf_u8,sizeof(uint8_t) *2,numsamples,fp);
    float *fdat = tbuf_f; // get a pointer to the float buffer
    uint8_t *sdat = tbuf_u8; // and the short buffer
    //process a half sample at a time
    for(unsigned int c = 0; c < numread * 2; c++)
    {
        *fdat = (((float)*sdat) / 127.5f) - 1; //convert from an unsigned 8 bit int (0->255) into a (-1 -> 1) float number
        fdat++;
        sdat++;
    }
    // write the processed samples into the output buffer
    buffer->write((complex<float> *)tbuf_f,numread);
    return numread;
}


