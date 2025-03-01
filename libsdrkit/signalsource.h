#ifndef SIGNALSOURCE_H
#define SIGNALSOURCE_H

#include <complex>
#include <fxpt_nco.h>
using namespace std;

/*
This class provides a SINE wave output
it's used for things like offset tuning
*/



class SignalSource
{
private:
    double		d_sampling_freq;
    double		d_frequency;
    double		d_ampl;
    complex<float>		d_offset;
    fxpt_nco	d_nco; // fixed point numerically controlled occilator

public:
    SignalSource();
    ~SignalSource();
    float getPhase(){return d_nco.get_phase();}
    void setPhase(float phase){d_nco.set_phase(phase);}
    int work(int noutput_items, complex<float> *output_items);
    double frequency() const { return d_frequency; }
    double amplitude() const { return d_ampl; }
    complex<float> offset() const { return d_offset; }

    void set_sampling_freq(double sampling_freq);
   // void set_waveform(gr_waveform_t waveform);
    void set_frequency(double frequency);
    void set_amplitude(double ampl);
    void set_offset(complex<float> offset);
};



#endif // SIGNALSOURCE_H


