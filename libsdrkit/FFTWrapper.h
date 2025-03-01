#ifndef FFTWRAPPER_H
#define FFTWRAPPER_H

/**
  * \file FFTWrapper.h
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
  * Description: Class to provide a simple API for the FFTDFT class.
  *
  * Platform: QRC WBT
  */

#include <cstddef>
#include "FFTDFT.h"


class FFTWrapper
{
public:

    //! Constructor.
    FFTWrapper( std::size_t nSamples );

    //! Destructor.
    ~FFTWrapper();

    //! Perform FFT and create FFT magnitude from real and imaginary arrays.
    void Execute();

    /*! Get the number of IQ and FFT samples.
     * @return - number of IQ and FFT samples
     */
    int GetSize() const { return m_nSamples; }
    void SetSize(int num_samples);

    /*! Get a pointer to the input (I&Q) array.
     * @return - Pointer to the input array.
     */
    FComplex* GetInputArray() { return m_inIQ; }

    /*! Get a pointer to the FFT magnitude array.
     * @return - Pointer to the FFT magnitude array
     */
    const float* GetFFTMagnitudeArray() const { return m_fftMagnitude; }

private:

    //! Number of FFT and I&Q samples.
    std::size_t m_nSamples;

    //! Pointer to the dynamically allocated input I&Q array.
    FComplex* m_inIQ;

    //! Pointer to the dynamically allocated FFT magnitude array.
    float* m_fftMagnitude;

    //! FFTDFT object for peforming FFTs.
    FFTDFT m_fft;
};

#endif // FFTWRAPPER_H
