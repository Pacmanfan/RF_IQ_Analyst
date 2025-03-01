#include "resampler_ff.h"
#include <math.h>

resampler_ff::resampler_ff()
{
    atten = 60; // 60db attenuation
    filter_width = 0.1f;
    rate = 0.25f;
    created = false;
    create_resampler_ff();
}

resampler_ff::~resampler_ff()
{
    destroy_resampler_ff();
}


void resampler_ff::set_rate(float rt)
{
    // output / input rate
    rate = rt;
    //create_resampler_ff();
    resamp_rrrf_set_rate(resamp,rate);
}

void resampler_ff::set_attenuation(float attn)
{
    atten = attn;
    create_resampler_ff();
}

/*
0 to 1 normalized frequency
*/
void resampler_ff::set_filter_width(float width)
{
    filter_width = width;
    create_resampler_ff();
}


void resampler_ff::create_resampler_ff()
{
    destroy_resampler_ff();

    unsigned int m    = 13;     // resampling filter semi-length (filter delay)
    unsigned int npfb = 64;     // number of filters in bank (timing resolution)

    // create resampler
    resamp = resamp_rrrf_create(rate,m,filter_width,atten,npfb);
    created = true;
}

void resampler_ff::destroy_resampler_ff()
{
    if(created)
    {
        // clean up allocated objects
        resamp_rrrf_destroy(resamp);
        created = false;
    }
}


void resampler_ff::resample(float *input,float *output, unsigned int numsamples_in,unsigned int *numsamples_out)
{
    resamp_rrrf_execute_block(resamp, input, numsamples_in, output, numsamples_out);
}
