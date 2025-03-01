#ifndef FFT_BUILDER_H
#define FFT_BUILDER_H
#include <liquid/liquid.h>
#include <sampleindexer.h>
#include <fft_filter.h>
#include <signalsource.h>

#include <fft_fftw.h>

#undef USE_CUDA // not using for now...

#ifdef USE_CUDA
    #include <fft_cuda.h>
#endif

#ifdef USE_IPP
    #include <fft_ipp.h>
#endif

#include <fft_hist.h>
#include <datarange.h>

/*
    This class builds the fft cache
    in each fft_helper class instance
    based on the current fft rate and fft bin size

*/
class FFT_Builder
{
public:
    long sampleindex; // where we are in the file (sample / time index) - top of the Waterfall
    bool m_usePSD; // calculate Power Spectrum density instead of FFT
    bool m_updatemax; // update the max vals of the fft
#ifdef USE_CUDA
    fft_cuda *m_fftcalc;
#else
    #ifdef USE_IPP
        fft_ipp *m_fftcalc;
    #else
        fft_fftw    *m_fftcalc;
    #endif
#endif

    FFT_Filter *m_filter;
    SignalSource *m_sigsrc;
    FFT_Builder();
    int startidx,endidx;
    void SetIndexer(SampleIndexer *indexer){m_indexer = indexer;}
    void SetFFTHist(FFT_Hist *hist){m_fft_hist = hist;}
    void SetPSD(bool val){m_usePSD = val;}
    void SetUpdateMax(bool val){m_updatemax = val;}
    void PanFFT(int val);
    void PanCache(int rows);
    void Build(bool invalidate = false);
    void Build(float *cache);
    void GotoTop();
    void GotoSampleIndex(long idx);
    void GotoTimeStamp(double timestamp);
    void SetFFTSize(int sz);
    double GetTopTimestamp();
    double GetBottomTimestamp();
    datarange GetTimeRange();
    void SetFilter(FFT_Filter *filter){m_filter = filter;}
    void SetSigSource(SignalSource *sigsrc){m_sigsrc = sigsrc;}
private:
    //reference to some objects we're using
    SampleIndexer *m_indexer;
    FFT_Hist *m_fft_hist;
};

#endif // FFT_BUILDER_H
