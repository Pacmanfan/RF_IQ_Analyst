#ifndef FFT_FILTER_H
#define FFT_FILTER_H

#include <math.h>
#include "liquid/liquid.h"
#include <complex>
using namespace std;

class FFT_Filter
{
public:
    FFT_Filter();
    ~FFT_Filter();
    void Filter(complex<float> *datain, complex<float> * dataout, int num_samples);
    void SetupFilter(float freqNorm, float stopatten, int filtlen);
private:
    void Release();
    firfilt_crcf m_filt;
    float *fcoef;
};

#endif // FFT_FILTER_H
