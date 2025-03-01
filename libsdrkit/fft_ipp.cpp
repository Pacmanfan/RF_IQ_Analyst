
#ifdef USE_IPP
#include <fft_ipp.h>
#include <memory>
#include <string.h>

//Set the size
void Temp()
{
    const int N=128;
    const int order=(int)(log((double)N)/log(2.0));

    // Spec and working buffers

    IppsFFTSpec_C_32fc *pFFTSpec=0; // complex to complex fft
    Ipp8u *pFFTSpecBuf, *pFFTInitBuf, *pFFTWorkBuf;

    // Allocate complex buffers

    Ipp32fc *pSrc=ippsMalloc_32fc(N);
    Ipp32fc *pDst=ippsMalloc_32fc(N);

    // Query to get buffer sizes

    int sizeFFTSpec,sizeFFTInitBuf,sizeFFTWorkBuf;
    ippsFFTGetSize_C_32fc(order, IPP_FFT_NODIV_BY_ANY, ippAlgHintAccurate, &sizeFFTSpec, &sizeFFTInitBuf, &sizeFFTWorkBuf);

    // Alloc FFT buffers
    pFFTSpecBuf = ippsMalloc_8u(sizeFFTSpec);
    pFFTInitBuf = ippsMalloc_8u(sizeFFTInitBuf);
    pFFTWorkBuf = ippsMalloc_8u(sizeFFTWorkBuf);

    // Initialize FFT

    ippsFFTInit_C_32fc(&pFFTSpec, order, IPP_FFT_NODIV_BY_ANY, ippAlgHintAccurate, pFFTSpecBuf, pFFTInitBuf);
    if (pFFTInitBuf)
            ippFree(pFFTInitBuf);

    // Do the FFT
    ippsFFTFwd_CToC_32fc(pSrc,pDst,pFFTSpec,pFFTWorkBuf);

    //check results
    ippsFFTInv_CToC_32fc(pDst,pDst,pFFTSpec,pFFTWorkBuf);
    int OK=1;
    for (int i=0;i<N;i++)
    {
      pDst[i].re/=(Ipp32f)N;
      pDst[i].im/=(Ipp32f)N;
      if ((fabs(pSrc[i].re-pDst[i].re)>.001) ||  (fabs(pSrc[i].im-pDst[i].im)>.001) )
      {
              OK=0;
              break;
      }
    }

    //puts(OK==1?"FFT OK":"FFT Fail");

    if (pFFTWorkBuf) ippFree(pFFTWorkBuf);
    if (pFFTSpecBuf) ippFree(pFFTSpecBuf);

    ippFree(pSrc);
    ippFree(pDst);

}


fft_ipp::fft_ipp()
{
    pFFTSpecBuf = nullptr;
    pFFTInitBuf = nullptr;
    pFFTWorkBuf = nullptr;
    pSrc = nullptr;
    pDst = nullptr;
    pFFTSpec = nullptr;

}

fft_ipp::~fft_ipp()
{
    FreeMem();
}

void fft_ipp::PerformFFT(complex<float> *inIQ, float *outFFT, unsigned int numsamples)
{
    const int order=(int)(log((double)numsamples)/log(2.0));

    if(numsamples != fftsize)
    {
        fftsize = numsamples;
        //changed, change the plan
        if(plancreated)
        {
            //de-allocate
            FreeMem();
        }
        plancreated = true;
        //(re)create the plan

        // Allocate complex buffers

        pSrc=ippsMalloc_32fc(numsamples);

        pDst=ippsMalloc_32fc(numsamples);

        // Query to get buffer sizes

        int sizeFFTSpec,sizeFFTInitBuf,sizeFFTWorkBuf;
        ippsFFTGetSize_C_32fc(order, IPP_FFT_NODIV_BY_ANY, ippAlgHintAccurate, &sizeFFTSpec, &sizeFFTInitBuf, &sizeFFTWorkBuf);

        // Alloc FFT buffers
        pFFTSpecBuf = ippsMalloc_8u(sizeFFTSpec);
        pFFTInitBuf = ippsMalloc_8u(sizeFFTInitBuf);
        pFFTWorkBuf = ippsMalloc_8u(sizeFFTWorkBuf);

        // Initialize FFT

//        ippsFFTInit_C_32fc(&pFFTSpec, order, IPP_FFT_NODIV_BY_ANY, ippAlgHintAccurate, pFFTSpecBuf, pFFTInitBuf);
        ippsFFTInit_C_32fc(&pFFTSpec, order, IPP_FFT_NODIV_BY_ANY, ippAlgHintFast, pFFTSpecBuf, pFFTInitBuf);

        if (pFFTInitBuf)
        {
            ippFree(pFFTInitBuf);
        }

    }
    //copy the samples in so we can perform the fft
    memcpy(pSrc,inIQ,numsamples * sizeof(complex<float>));

    // Do the FFT
    ippsFFTFwd_CToC_32fc(pSrc,pDst,pFFTSpec,pFFTWorkBuf);
    // everything following here can probably be done with the intel performance primitives
    // now convert to magnitude

    float *co = (float*)pDst;// get a pointer to the complex<float> out
    // ----- Normalize In-Place-----
    Ipp32fc val;
    val.re = numsamples;
    val.im = numsamples;
    ippsDivC_32fc_I(val,pDst, fftsize);
    //compute power and copy to outFFT

    // Amount to scale the FFT.

    const float pwroffset = -50.0;

    const float fScale = 10.0f;
    // Calculate FFT magnitude for the second half of the spectrum using the
    // first half of the I&Q data.
    uint32_t nHalf = fftsize / 2;
    for( uint32_t i=0; i < nHalf; ++i )
    {
        const float re = pDst[i].re;
        const float im = pDst[i].im;

        const uint32_t nIndex = i + nHalf;
        outFFT[nIndex] = fScale * ::log10(::sqrt( re * re + im * im )) + pwroffset;
    }

    // Calculate FFT magnitude for the first half of the spectrum using the
    // second half of the I&Q data.
    for( uint32_t i=nHalf; i < fftsize; ++i )
    {
        const float re = pDst[i].re;
        const float im = pDst[i].im;
        const uint32_t nIndex = i - nHalf;
        outFFT[nIndex] = fScale * ::log10(::sqrt( re * re + im * im )) + pwroffset;
    }

}


/*
Same as above, but we calculate the phase as well
*/
void fft_ipp::PerformFFT(complex<float> *inIQ, float *outFFTMag, float *outFFTPhase, unsigned int numsamples)
{
    const int order=(int)(log((double)numsamples)/log(2.0));

    if(numsamples != fftsize)
    {
        fftsize = numsamples;
        //changed, change the plan
        if(plancreated)
        {
            //de-allocate
            FreeMem();
        }
        plancreated = true;
        //(re)create the plan

        // Allocate complex buffers

        pSrc=ippsMalloc_32fc(numsamples);

        pDst=ippsMalloc_32fc(numsamples);

        // Query to get buffer sizes

        int sizeFFTSpec,sizeFFTInitBuf,sizeFFTWorkBuf;
        ippsFFTGetSize_C_32fc(order, IPP_FFT_NODIV_BY_ANY, ippAlgHintAccurate, &sizeFFTSpec, &sizeFFTInitBuf, &sizeFFTWorkBuf);

        // Alloc FFT buffers
        pFFTSpecBuf = ippsMalloc_8u(sizeFFTSpec);
        pFFTInitBuf = ippsMalloc_8u(sizeFFTInitBuf);
        pFFTWorkBuf = ippsMalloc_8u(sizeFFTWorkBuf);

        // Initialize FFT

        ippsFFTInit_C_32fc(&pFFTSpec, order, IPP_FFT_NODIV_BY_ANY, ippAlgHintAccurate, pFFTSpecBuf, pFFTInitBuf);
        if (pFFTInitBuf)
        {
            ippFree(pFFTInitBuf);
        }

    }
    //copy the samples in so we can perform the fft
    memcpy(pSrc,inIQ,numsamples * sizeof(complex<float>));

    // Do the FFT
    ippsFFTFwd_CToC_32fc(pSrc,pDst,pFFTSpec,pFFTWorkBuf);
    // everything following here can probably be done with the intel performance primitives
    // now convert to magnitude

    float *co = (float*)pDst;// get a pointer to the complex<float> out
    // ----- Normalize In-Place-----
    Ipp32fc val;
    val.re = numsamples;
    val.im = numsamples;
    ippsDivC_32fc_I(val,pDst, fftsize);
    //compute power and copy to outFFT

    // Amount to scale the FFT.

    const float pwroffset = -50.0;

    const float fScale = 10.0f;
    // Calculate FFT magnitude for the second half of the spectrum using the
    // first half of the I&Q data.
    uint32_t nHalf = fftsize / 2;
    for( uint32_t i=0; i < nHalf; ++i )
    {
        const float re = pDst[i].re;
        const float im = pDst[i].im;

        const uint32_t nIndex = i + nHalf;
        outFFTMag[nIndex] = fScale * ::log10(::sqrt( re * re + im * im )) + pwroffset;
        outFFTPhase[nIndex] = atan2(re,im);
    }

    // Calculate FFT magnitude for the first half of the spectrum using the
    // second half of the I&Q data.
    for( uint32_t i=nHalf; i < fftsize; ++i )
    {
        const float re = pDst[i].re;
        const float im = pDst[i].im;
        const uint32_t nIndex = i - nHalf;
        outFFTMag[nIndex] = fScale * ::log10(::sqrt( re * re + im * im )) + pwroffset;
        outFFTPhase[nIndex] = atan2(re,im);
    }
}

void fft_ipp::FreeMem()
{
    //ippFree(pFFTInitBuf);
    if (pFFTWorkBuf)
        ippFree(pFFTWorkBuf);
    if (pFFTSpecBuf)
        ippFree(pFFTSpecBuf);
    ippFree(pSrc);
    ippFree(pDst);


}
#endif // USE_IPP
