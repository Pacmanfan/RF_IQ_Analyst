#include "resampler_arb.h"
#include <math.h>

resampler_arb::resampler_arb()
{
    atten = 60; // 60db attenuation
    filter_width = 0.1f;
    rate = 0.25f;
    created = false;
    inuse = false;
    create_resampler_arb();

}

resampler_arb::~resampler_arb()
{
    destroy_resampler_arb();
}


void resampler_arb::set_rate(float rt)
{
    // output / input rate
    rate = rt;
    //create_resampler_arb();
    resamp_crcf_set_rate(resamp,rate);
    //resamp_crcf_print(resamp);
}

void resampler_arb::set_attenuation(float attn)
{
    atten = attn;
    create_resampler_arb();
}

/*
0 to 1 normalized frequency
*/
void resampler_arb::set_filter_width(float width)
{
    filter_width = width;
    create_resampler_arb();
}

void resampler_arb::create_resampler_arb()
{
    while (inuse){} // wait for it to not be in use
    inuse = true;
    destroy_resampler_arb();

    unsigned int m    = 13;     // resampling filter semi-length (filter delay)
    unsigned int npfb = 64;     // number of filters in bank (timing resolution)

    if(filter_width > .5 )
        filter_width = .49;//
    if(filter_width < 0)
        filter_width = 0.00001;

    // create resampler
    resamp = resamp_crcf_create(rate,m,filter_width,atten,npfb);
    created = true;
    inuse = false;
}

void resampler_arb::destroy_resampler_arb()
{
    if(created)
    {
        // clean up allocated objects
         resamp_crcf_destroy(resamp);
        created = false;
    }
}


void resampler_arb::resample(std::complex<float> *input, std::complex<float> *output, unsigned int numsamples_in, unsigned int *numsamples_out)
{
    while (inuse){} // wait for it to not be in use
    inuse = true;
    //liquid_float_complex *indat,*outdat;
    //indat = (liquid_float_complex *)input;
    //outdat = (liquid_float_complex *)output;
    resamp_crcf_execute_block(resamp, (liquid_float_complex *)input, numsamples_in, (liquid_float_complex *)output, numsamples_out);
    inuse = false;
}
