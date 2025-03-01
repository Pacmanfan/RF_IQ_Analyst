%module sdrkit
%{
    /* the resulting C file should be built as a python extension */
    #define SWIG_FILE_WITH_INIT
    /*  Includes the header in the wrapper code */
    #include "burst_detector.h"
    #include "classifier.h"
    #include "data_exporter.h"
    #include "datarange.h"
    #include "dsp_utils.h"
    #include "feature_detector.h"
    #include "fft_builder.h"
    #include "fft_fftw.h"
    #include "FFTDFT.h"
    #include "fft_filter.h"
    #include "fft_hist2.h"
    #include "fft_hist.h"
    #include "fft_ipp.h"
    #include "FFTWrapper.h"
    #include "file_resampler.h"
    #include "ftmarker.h"
    #include "fxpt.h"
    #include "fxpt_nco.h"
    #include "iq_16t.h"
    #include "iqdemodplayer.h"
    #include "iq_u8.h"
    #include "peak_detector.h"
    #include "qvrt_gps_reader.h"
    #include "resampler_arb.h"
    #include "resampler_ff.h"
    #include "resampler_polyphase_ipp_ff.h"
    #include "retrodf.h"
    #include "sampleindexer.h"
    #include "signaldetector.h"
    #include "signalsource.h"
    #include "signalstreamscanner.h"
    #include "signaltablemagextractor.h"
    #include "sigtuner.h"
    #include "sinetable.h"
    #include "srifile.h"
    #include "utils.h"

%}

/*  include the numpy typemaps */
%include "numpy.i"
%include <std_string.i>
%include <std_complex.i>
%include "stdint.i"
/*  need this for correct module initialization */

%init %{
    import_array();
%}


// Parse the original header file

%include "burst_detector.h"
%include "classifier.h"
%include "data_exporter.h"
%include "datarange.h"
%include "dsp_utils.h"
%include "feature_detector.h"
%include "fft_builder.h"
%include "fft_fftw.h"
%include "FFTDFT.h"
%include "fft_filter.h"
%include "fft_hist2.h"
%include "fft_hist.h"
%include "fft_ipp.h"
%include "FFTWrapper.h"
%include "file_resampler.h"
%include "ftmarker.h"
%include "fxpt.h"
%include "fxpt_nco.h"
%include "iq_16t.h"
%include "iqdemodplayer.h"
%include "iq_u8.h"
%include "peak_detector.h"
%include "qvrt_gps_reader.h"
%include "resampler_arb.h"
%include "resampler_ff.h"
%include "resampler_polyphase_ipp_ff.h"
%include "retrodf.h"
%include "sampleindexer.h"
%include "signaldetector.h"
%include "signalsource.h"
%include "signalstreamscanner.h"
%include "signaltablemagextractor.h"
%include "sigtuner.h"
%include "sinetable.h"
%include "srifile.h"
%include "utils.h"



