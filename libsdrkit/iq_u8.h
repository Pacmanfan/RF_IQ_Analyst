#ifndef IQ_U8_H
#define IQ_U8_H


class IQ_U8
{
public:
    IQ_U8();
};


#include <qvrt_tools.h>
#include <string>
#include <srifile.h>

using namespace std;

/*
This is used to read and write data to/from u8 formatted files

unsigned 8 bit interleaved samples in IQ order

*/

class IQ_U8_Writer : public IQ_Writer,public SRIFile
{
public:
    uint8_t *m_conv_buff;
    unsigned long m_conv_buff_len;
    IQ_U8_Writer();
    ~IQ_U8_Writer();

    void AddData(complex<float> *iq, unsigned int numsamples);
    bool Setup(int streamid,double CF_Hz, double SPS, double BW_Hz, double RFGain, double IFGain);

};

class IQ_U8_Reader : public IQ_Reader, public SRIFile
{
public:
    IQ_U8_Reader();
    ~IQ_U8_Reader();
    long ReadSamples(CircBuff<complex<float> > *buffer,unsigned int numsamples);
private:
    uint8_t *tbuf_u8;
    float *tbuf_f;
    size_t _sz;
    void Release();
};
#endif // IQ_U8_H
