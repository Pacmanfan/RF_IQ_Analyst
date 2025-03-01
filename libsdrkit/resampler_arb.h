#ifndef resampler_arb_H
#define resampler_arb_H

// This resampler_arb class is based off the liquid DSP code
// it performs arbitrary decimation/interpolation
// it performs filtering,
#include <liquid/liquid.h>
#include <complex>


using namespace std;

class resampler_arb
{
public:
    resampler_arb();
    ~resampler_arb();
    void set_rate(float rt); // output / input rate
    void set_attenuation(float atten);
    void set_filter_width(float width);

    float get_rate(){return rate;}
    float get_attenuation(){return atten;}
    float get_filter_width(){return filter_width;}
    void resample(std::complex<float> *input, std::complex<float> *output, unsigned int numsamples_in, unsigned int *numsamples_out);
private:
    float rate;
    float atten;
    float filter_width;
    resamp_crcf resamp;
    bool created;
    volatile bool inuse;
    void create_resampler_arb();
    void destroy_resampler_arb();
};

#endif // resampler_arb_H
