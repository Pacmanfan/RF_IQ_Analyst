#ifndef _FFTDFT_H_
#define _FFTDFT_H_

/**
  * \file FFTDFT.h
  * System: WBT
  * Component Name: WBT Sample App
  * Language: C++
  *
  * License: GNU Public License
  * Licensed material - property of
  * (c) Copyright QRC Technology, Inc., 2014
  *
  * Address:
  *  QRC Technology, Inc.
  *  1211 Central Park Blvd.
  *  Fredericksburg, VA 22401
  *
  * Description: Class to perform FFT or DFT.
  *
  * Platform: QRC WBT
  */

#include <stdint.h>

//! Structure used for complex floating point values. Use this instead of the C++ standard library template class.
struct FComplex
{
    float re;
    float im;
};

/*! FFTDFT class computes an FFT if a power of two is specified.
 *  If not, and zero padding is enabled, zero pads out to a power of two.
 *  If not, and zero padding is not enabled, performs a slow DFT.
 */
class FFTDFT
{
public:

    //! Constructor.
    FFTDFT( uint32_t numBins, bool bZeroPad, bool bDoHannWindow );

    //! Destructor.
    ~FFTDFT();

    //! Computes the complex FFT or DFT of the input and returns the results.
    const FComplex* Execute( FComplex* in );
    void SetSize(int numsamples);
private:

    //! Calculates the FFT of the input array, A.
    static void FFT( uint32_t n, FComplex* A, FComplex* W );

    //! Calculates DFT of the input array (very slow).
    static void DFT( uint32_t n, FComplex* in, FComplex* out );

    //! Calculates roots of unity.
    static void ComputeW( uint32_t n, FComplex* W );

    //! Permutes the array, x, using a bit-reversal permutation.
    static void Permute( uint32_t n, FComplex* x );

    //! Treats inp as a numbits number and bit-reverses it.
    static uint32_t Bitrev( uint32_t inp, uint32_t numbits );

    //! Returns log base 2 of n (if n is a power of 2).
    static uint32_t ilog2( uint32_t n );

    //! Computes a Hann window function of dimension m_nSamples.
    void ComputeHann();


    //! Static method to add FComplex objects together.
    static FComplex addFC( FComplex a, FComplex b );

    //! Static method to subtract FComplex objects.
    static FComplex subFC( FComplex a, FComplex b );

    //! Static method to multiply FComplex objects.
    static FComplex mltFC( FComplex a, FComplex b );

    //! Number of samples used as input (does not need to be power of two).
    uint32_t m_nSamples;

    //! Same as m_nSamples, unless zero padding is added.
    uint32_t m_nSize;

    //! Dynamically allocated FFT or DFT results. Dimension will be m_size.
    FComplex* m_output;

    //! Dynamically allocated array used for intermediate values. Dimension will be m_size.
    FComplex* m_W;

    //! Dynamically allocated array for hann filter. Dimesnion will be m_nSamples (do not window the zero padding).
    float* m_hann;

    //! Use FFT when true, DFT when false.
    bool m_bPowerOfTwo;

    //! True if samples should be padded to the next highest power of two.
    bool m_bZeroPad;

    //! True if Hann window should be applied to input data (does not affect padding).
    bool m_bDoHann;
};

#endif
