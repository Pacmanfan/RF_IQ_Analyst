#ifndef FFT_CUDA_H
#define FFT_CUDA_H

#ifdef USE_CUDA

#include <complex>
#include <cufft.h>
#include <cuda_runtime_api.h>
#include <cuda.h>

using namespace std;

class fft_cuda
{
public:
    fft_cuda();
    ~fft_cuda();
    void PerformFFT(complex<float> *inIQ, float *outFFT, unsigned int numsamples);
private:
    unsigned int fftsize;
    cufftHandle plan;
    cufftComplex *data;
    bool plancreated;


};
#endif // USE_CUDA
#endif // FFT_CUDA_H
