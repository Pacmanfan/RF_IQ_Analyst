#ifdef USE_CUDA
#include "fft_cuda.h"
#define BATCH 1

fft_cuda::fft_cuda()
{
    data = nullptr;
    plancreated = false;
    fftsize = 0;
}

fft_cuda::~fft_cuda()
{
    if(data != nullptr)
        cudaFree(data);

    if(plancreated == true)
        cufftDestroy(plan); /* Destroy the CUFFT plan. */
}

void fft_cuda::PerformFFT(complex<float> *inIQ, float *outFFT, unsigned int numsamples)
{
    if(numsamples != fftsize) // FFT size is changing
    {
        fftsize = numsamples;
        if(data != nullptr) // free any previously allocated memory
            cudaFree(data);
        //allocate memory for the fft
        cudaMalloc((void**)&data, sizeof(cufftComplex)*fftsize*BATCH);/* Create a 1D FFT plan. */

        if(plancreated == true)
        {
            cufftDestroy(plan); /* Destroy the CUFFT plan. */
            plancreated = false;
        }

        //create new plan
        cufftPlan1d(&plan, numsamples, CUFFT_C2C, BATCH); /* Use the CUFFT plan to transform the signal in place. */
        plancreated = true;
    }
    // execute the complex to complex FFT using cuda as an in-place operation
    cufftExecC2C(plan, data, data, CUFFT_FORWARD);
}



/*
void Test()
{
    cudaMalloc((void**)&data, sizeof(cufftComplex)*NX*BATCH);// Create a 1D FFT plan.
    cufftPlan1d(&plan, NX, CUFFT C2C, BATCH); // Use the CUFFT plan to transform the signal in place.
    cufftExecC2C(plan, data, data, CUFFT FORWARD); // Destroy the CUFFT plan.

}
    */
#endif // USE_CUDA
