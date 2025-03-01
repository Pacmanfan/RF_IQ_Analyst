#ifndef IQ_16T_H
#define IQ_16T_H
#include <qvrt_tools.h>
#include <string>
#include <srifile.h>

using namespace std;

/*
This is used to read and write data to/from 16T/ S16 formatted files
Signed 16 bit interleaved format in IQ order

*/

class IQ_16T_Writer : public IQ_Writer,public SRIFile
{
public:
    short *m_conv_buff;
    unsigned long m_conv_buff_len;
    IQ_16T_Writer();
    ~IQ_16T_Writer();

    void AddData(complex<float> *iq, unsigned int numsamples);
    bool Setup(int streamid,double CF_Hz, double SPS, double BW_Hz, double RFGain, double IFGain);

};

class IQ_16T_Reader : public IQ_Reader, public SRIFile
{
public:
    IQ_16T_Reader();
    ~IQ_16T_Reader();
    long ReadSamples(CircBuff<complex<float> > *buffer,unsigned int numsamples);
private:
    short *tbuf_s;
    float *tbuf_f;
    size_t _sz;
    void Release();
};

#endif // IQ_16T_H
