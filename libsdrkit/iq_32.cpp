#include "iq_32.h"


IQ_32_Writer::IQ_32_Writer() : IQ_Writer(), SRIFile()
{
}

IQ_32_Writer::~IQ_32_Writer()
{

}

void IQ_32_Writer::AddData(complex<float> *iq, unsigned int numsamples)
{
    //write the data to the file
    fwrite(iq , sizeof(complex<float>) * numsamples,1,fp);
}

bool IQ_32_Writer::Setup(int streamid,double CF_Hz, double aSPS, double BW_Hz, double RFGain, double IFGain)
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

IQ_32_Reader::IQ_32_Reader()
{
    _sz = 0;
}

IQ_32_Reader::~IQ_32_Reader()
{

}

long IQ_32_Reader::ReadSamples(CircBuff<complex<float> > *buffer,unsigned int numsamples)
{
    // re-allocate memeory if needed
    if(_sz < numsamples *2)
    {
        tbuf_f = new float[ numsamples *2];
        _sz = numsamples;
    }
    size_t numread = fread(tbuf_f,sizeof(complex<float>),numsamples,fp);
    buffer->write((complex<float> *)tbuf_f,numread);
    return numread;
}
