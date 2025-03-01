#include "fft_filter.h"
#include <complex>
using namespace std;

FFT_Filter::FFT_Filter()
{
    fcoef = 0;
}

FFT_Filter::~FFT_Filter()
{
    Release();
}

void FFT_Filter::Release()
{
    if(fcoef != 0)
    {
        delete []fcoef;
        fcoef = 0;
        firfilt_crcf_destroy(m_filt);
    }

}
void FFT_Filter::SetupFilter(float freqNorm, float stopatten, int filtlen)
{
    Release();
    // create new co-efficients array
    fcoef = new float[filtlen];

    /*
    // design filter co-effcients
    liquid_firdes_kaiser(filtlen, freqNorm, stopatten, 0, fcoef);

    // design regular FIR filter
    m_filt = firfilt_crcf_create(fcoef, filtlen);
    */
    m_filt = firfilt_crcf_create_kaiser(filtlen, freqNorm, stopatten, 0.0f);

    firfilt_crcf_set_scale(m_filt, 2.0f * freqNorm);

}

void FFT_Filter::Filter(complex<float> *datain, complex<float> * dataout, int num_samples)
{
    int i;
    liquid_float_complex *x = (liquid_float_complex * ) datain;
    liquid_float_complex *y0 = (liquid_float_complex *) dataout;
  //  complex<float> *x = (complex<float> * ) datain;
  //  complex<float> *y0 = (complex<float> *) dataout;

    // run signal through regular filter one sample at a time
    for (i=0; i < num_samples; i++)
    {
        // run filter
        firfilt_crcf_push(m_filt, x[i]);
        firfilt_crcf_execute(m_filt, &y0[i]);
    }

}
