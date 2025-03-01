#ifndef RESAMPLER_FF_H
#define RESAMPLER_FF_H

// This resampler class is based off the liquid DSP code
// it performs arbitrary decimation/interpolation
// it performs filtering, as well as offset tuning
#include <liquid/liquid.h>
#include <complex>
using namespace std;

class resampler_ff
{
public:
    resampler_ff();
    ~resampler_ff();
    void set_rate(float rt); // output / input rate
    void set_attenuation(float atten);
    void set_filter_width(float width);

    float get_rate(){return rate;}
    float get_attenuation(){return atten;}
    float get_filter_width(){return filter_width;}
    void resample(float *input,float *output, unsigned int numsamples_in,unsigned int *numsamples_out);
private:
    float rate;
    float atten;
    float filter_width;
    resamp_rrrf resamp;
    bool created;
    void create_resampler_ff();
    void destroy_resampler_ff();
};
#endif // RESAMPLER_FF_H
