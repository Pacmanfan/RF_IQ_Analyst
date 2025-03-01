#ifndef FFT_IPP_H
#define FFT_IPP_H
#ifdef USE_IPP

#include <complex>
#include <ipp.h>
#include <math.h>
using namespace std;

class fft_ipp
{
public:
    fft_ipp();
    ~fft_ipp();
    void PerformFFT(complex<float> *inIQ, float *outFFT, unsigned int numsamples);
    void PerformFFT(complex<float> *inIQ, float *outFFTMag, float *outFFTPhase, unsigned int numsamples);
private:
    unsigned int fftsize;

    bool plancreated;
    Ipp8u *pFFTSpecBuf, *pFFTInitBuf, *pFFTWorkBuf;
    Ipp32fc *pSrc;
    Ipp32fc *pDst;

    IppsFFTSpec_C_32fc *pFFTSpec; // complex to complex fft plan
    void FreeMem();

};
#endif
#endif // FFT_IPP_H
