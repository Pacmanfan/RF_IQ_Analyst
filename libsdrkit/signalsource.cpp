#include "signalsource.h"
#ifndef M_PI
#define M_PI 3.14159265359
#endif

SignalSource::SignalSource()
{
    d_offset = complex<float>(0,0);
}

SignalSource::~SignalSource()
{
}


int SignalSource::work(int noutput_items,complex<float> *output_items)
{
    complex<float> *optr = output_items;
    d_nco.sincos(optr, noutput_items, d_ampl);

    if(d_offset == complex<float>(0,0))
        return noutput_items;

    for(int i = 0; i < noutput_items; i++)
    {
        optr[i] += d_offset;
    }

    return noutput_items;
}

void SignalSource::set_sampling_freq(double sampling_freq)
{
    d_sampling_freq = sampling_freq;
    d_nco.set_freq ((float)(2 * M_PI * d_frequency / d_sampling_freq));
}


void SignalSource::set_frequency(double frequency)
{
    d_frequency = frequency;
    d_nco.set_freq((float)(2 * M_PI * d_frequency / d_sampling_freq));
}

void SignalSource::set_amplitude(double ampl)
{
    d_ampl = ampl;
}

void SignalSource::set_offset(complex<float> offset)
{
    d_offset = offset;
}

