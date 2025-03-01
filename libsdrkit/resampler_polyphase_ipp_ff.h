#ifndef resampler_polyphase_ipp_ff_H
#define resampler_polyphase_ipp_ff_H

// This resampler_polyphase_ipp_ff class is based off the Intel Performance primitives
/*
reampling code, if performs float to float resampling of a stream
the streams must be aligned and allocated using the XX and YY functions
it performs arbitrary decimation/interpolation
it performs filtering using a polyphase filter bank
*/

#ifdef USE_IPP

#include <ipps.h>
#include <ippcore.h>
#include <ippvm.h>


using namespace std;

class resampler_polyphase_ipp_ff
{
public:
    resampler_polyphase_ipp_ff();
    ~resampler_polyphase_ipp_ff();
    void set_rate(float rt); // output / input rate
    void set_attenuation(float atten);
    void set_filter_width(float width);

    float get_rate(){return rate;}
    float get_attenuation(){return atten;}
    float get_filter_width(){return filter_width;}
  //  void resample(std::complex<float> *input, std::complex<float> *output, unsigned int numsamples_in, unsigned int *numsamples_out);
private:
    float rate;
    float atten;
    float filter_width;
  //  resamp_crcf resamp;
    bool created;
    volatile bool inuse;
    void create_resampler_polyphase_ipp_ff();
    void destroy_resampler_polyphase_ipp_ff();
};

#endif // resampler_polyphase_ipp_ff_H
#endif // USE_IPP
