#ifndef IQ_32_H
#define IQ_32_H

#include <qvrt_tools.h>
#include <string>
#include <srifile.h>

using namespace std;

/*
This is used to read and write data to/from raw and cfile Interleaved 2 chjannel 32-bit formatted files
32 bit interleaved format in IQ order

*/

class IQ_32_Writer : public IQ_Writer , public SRIFile
{
public:
    IQ_32_Writer();
    ~IQ_32_Writer();

    void AddData(complex<float> *iq, unsigned int numsamples);
    bool Setup(int streamid,double CF_Hz, double SPS, double BW_Hz, double RFGain, double IFGain);
};

class IQ_32_Reader : public IQ_Reader, public SRIFile
{
public:
    IQ_32_Reader();
    ~IQ_32_Reader();
    long ReadSamples(CircBuff<complex<float> > *buffer,unsigned int numsamples);
private:

    float *tbuf_f;
    size_t _sz;
    void Release();
};

#endif // IQ_16T_H
