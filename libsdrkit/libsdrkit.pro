#-------------------------------------------------
#
# Project created by QtCreator 2018-05-15T10:19:16
#
#-------------------------------------------------

QT       += core gui network widgets
TARGET = sdrkit
CONFIG += staticlib c++14

_JENKINSBUILD = $$(JENKINSBUILD) # set the local var so it can be used

isEmpty(_JENKINSBUILD) {
    TEMPLATE = lib
}else {
    win32:TEMPLATE = vclib
    else: TEMPLATE = lib
}


CODE_LIB = $$(HTL_CODE_LIBRARY)
isEmpty(CODE_LIB){
    # this is hard coded based on location of this file to code library
    # most windows checkouts
    CODE_LIB = $$PWD"/../codelibrary/win/64bit/vs2017/codelibrary/3rdparty"
}

##----------------Intel IPP detection and usage
IPP_DIR = /opt/intel/ipp
exists( $$IPP_DIR ) {
      message( "Intel Performance Primitives detected" )
    DEFINES += USE_IPP
    INCLUDEPATH += /opt/intel/ipp/include
    LIBS += -lippcore -lippi -lippi_tl -lipps -lippvm # intel Performance primitives
}

##----------------CUDA Stuff
... # QT, SOURCES, HEADERS, the usual stuff

CUDA_DIR = /usr/local/cuda-10.2/

exists( $$CUDA_DIR ) {
      message( "CUDA detected" )
CUDA_SOURCES += \
    vectorAdd.cu
    DEFINES += USE_CUDA
    CUDA_ARCH = sm_32 # as supported by the Tegra K1
    INCLUDEPATH += $$CUDA_DIR/include
    LIBS += -L $$CUDA_DIR/lib -lcudart -lcuda
    cuda.commands = $$CUDA_DIR/bin/nvcc -c -arch=$$CUDA_ARCH  -o ${QMAKE_FILE_OUT} ${QMAKE_FILE_NAME}
    cuda.dependency_type = TYPE_C
    cuda.depend_command = $$CUDA_DIR/bin/nvcc -M ${QMAKE_FILE_NAME}
    cuda.input = CUDA_SOURCES
    cuda.output = ${QMAKE_FILE_BASE}_cuda.o
    QMAKE_EXTRA_COMPILERS += cuda
}

##----------------End cuda stuff



win32 {
    # header-only includes are common to both windows build types.

    # liquid-dsp JSON
    INCLUDEPATH += $$CODE_LIB"/liquid-dsp/include"

    # nlohmann JSON
    INCLUDEPATH += $$CODE_LIB"/nlohmann/v3.10.1/"

    #Eigen (Header only stuff)
    INCLUDEPATH += $$CODE_LIB"/eigen/eigen-3.3.7"

    # proto
    PROTO_LOCATION = $$CODE_LIB"/gpb/2.6.1"


    win32-g++:{

        LIBS += -lws2_32
        LIBS += -lwsock32


        QMAKE_CFLAGS += -Os -Wa, -mbig-obj
        QMAKE_CXXFLAGS += -Os
        QMAKE_LFLAGS += -Wl,--allow-multiple-definition,-flto

        #Boost 1.78 (later versions needed for boost:beast)
        INCLUDEPATH += $$CODE_LIB"/boost/boost_1_78_0/include/boost-1_78"

        LIBS += -L$$CODE_LIB"/boost/boost_1_78_0/lib"

        Debug: BOOST_LIB_SUFFIX = -mgw7-mt-d-x64-1_78
        Release: BOOST_LIB_SUFFIX = -mgw7-mt-x64-1_78

        LIBS += -llibboost_thread$$BOOST_LIB_SUFFIX
        LIBS += -llibboost_date_time$$BOOST_LIB_SUFFIX
        LIBS += -llibboost_chrono$$BOOST_LIB_SUFFIX
        LIBS += -llibboost_filesystem$$BOOST_LIB_SUFFIX

        #Log4CPlus
        INCLUDEPATH += $$CODE_LIB"/log4cplus-2.0.6/include"
        LIBS += -L$$CODE_LIB"/log4cplus-2.0.6/build/bin"
        LIBS += -llog4cplusU

        #Google Protocol Buffers
        INCLUDEPATH += $$CODE_LIB"/protobuf-2.6.1/src"
        LIBS += -L$$CODE_LIB"/protobuf-2.6.1/src/.libs"
        LIBS += -llibprotobuf

        #openssl / libcrypto
        INCLUDEPATH += $$CODE_LIB"/openssl/include"
        LIBS += -L$$CODE_LIB"/openssl/"
        LIBS += -lssl -lcrypto

        #windows socket stuff
        LIBS += -lws2_32
        LIBS += -lwsock32

        #PortAudio
        INCLUDEPATH += $$CODE_LIB"/portaudio/v19/include"
        LIBS += -L$$CODE_LIB"/portaudio/v19/lib"
        LIBS += -lportaudio_x64

    }

    #libraries and headers for the MSVC build of the libraries
    win32-msvc:{
        #Boost 1.78 (later versions needed for boost:beast)
        INCLUDEPATH += $$CODE_LIB"/boost/boost_1_78_0/include/"
        LIBS += -L$$CODE_LIB"/boost/boost_1_78_0/lib_msvc141"
        Debug: BOOST_LIB_SUFFIX = -vc141-mt-gd-x64-1_78
        Release: BOOST_LIB_SUFFIX = -vc141-mt-x64-1_78
        LIBS += -llibboost_thread$$BOOST_LIB_SUFFIX
        LIBS += -llibboost_date_time$$BOOST_LIB_SUFFIX
        LIBS += -llibboost_chrono$$BOOST_LIB_SUFFIX
        LIBS += -llibboost_filesystem$$BOOST_LIB_SUFFIX
        LIBS += -L$$CODE_LIB"/liquid-dsp"
        LIBS += -llibliquid


        #log4cplus
        INCLUDEPATH += $$CODE_LIB"/log4cplus/2.0.5/include"
        LIBS += -L$$CODE_LIB"/log4cplus/2.0.5/lib"
        Debug: LOG4CPLUS_SUFFIX = -vc150D
        Release: LOG4CPLUS_SUFFIX = -vc150
        LIBS += -llog4cplus$$LOG4CPLUS_SUFFIX

        #Google Protocol Buffers
        INCLUDEPATH += $$CODE_LIB"/gpb/2.6.1/c++"
        LIBS += -L$$CODE_LIB"/gpb/2.6.1/c++/lib"
        Release:LIBS += -llibprotobuf
        Debug:LIBS += -llibprotobufd

        #openssl / libcrypto #using the 1.0.2 version
        INCLUDEPATH += $$CODE_LIB"/openssl/openssl-1.0.2t/include"
        LIBS += -L$$CODE_LIB"/openssl/openssl-1.0.2t/lib"
        LIBS += -llibeay32 -lssleay32

        # fftw  - fast fourier transform code
        INCLUDEPATH +=  $$CODE_LIB"/fftw/fftw-3.3.5/include"
        LIBS += -L$$CODE_LIB"/fftw/fftw-3.3.5/lib" -llibfftw3-3

        #PortAudio
        INCLUDEPATH += $$CODE_LIB"/portaudio/v19/include"
        LIBS += -L$$CODE_LIB"/portaudio/v19/lib"
        LIBS += -lportaudio_x64
    }
}

!win32 {
    # this is needed with older compilers
    QMAKE_CXXFLAGS += -I $$[QT_INSTALL_HEADERS]
    # most libraries
    HTL_THIRD_PARTY_BASE_PATH = $$(HTL_THIRD_PARTY_BASE)
    !isEmpty(HTL_THIRD_PARTY_BASE_PATH) {
        QMAKE_CXXFLAGS += -isystem $$(HTL_THIRD_PARTY_BASE)/include
        LIBS += -L$${HTL_THIRD_PARTY_BASE}/lib/
        QWT_LIB_PATH = -lqwt

        # Note: --enable-new-dtags changes rpath to set RUNPATH instead of RPATH
        # Note 2: below is only for development. The stage scripts
        # (linuxdeployqt) should ultimately override the RUNPATH
        QMAKE_LFLAGS *= "--enable-new-dtags -Wl,-rpath=$${HTL_THIRD_PARTY_BASE_PATH}/lib"
    }
}




include(../qvrt_lib/qvrt_util/qvrt_util.pri)
#LIBS += -lboost_system
LIBS += -lfftw3f

SOURCES += \
    dsp_utils.cpp \
    fft_builder.cpp \
    fft_cuda.cpp \
    fft_fftw.cpp \
    iq_32.cpp \
    iq_u8.cpp \
    resampler_polyphase_ipp_ff.cpp \
    sampleindexer.cpp \
    peak_detector.cpp \
    fft_hist.cpp \
    qcustomplot.cpp \
    ftmarker.cpp \
    fft_filter.cpp \
    signaldetector.cpp \
    signalsource.cpp \
    fxpt.cpp \
    signalstreamscanner.cpp \
    signaltablemagextractor.cpp \
    srifile.cpp \
    feature_detector.cpp \
    burst_detector.cpp \
    file_resampler.cpp \
    cnpy.cpp \
    iq_16t.cpp \
    classifier.cpp \
    data_exporter.cpp \
    pluginmanager.cpp \
    iqdemodplayer.cpp \
    resampler_ff.cpp \
    resampler_arb.cpp \
    sigtuner.cpp \
    ftmarker_gui.cpp \
    sigtuner_gui.cpp \
    utils.cpp \
    wgt_util.cpp \
    qvrt_gps_reader.cpp \
    fft_hist2.cpp \
    pluginbase.cpp

HEADERS += libsdrkit.h \
    dsp_utils.h \
    fft_cuda.h \
    fft_fftw.h \
    iq_32.h \
    iq_u8.h \
    resampler_polyphase_ipp_ff.h \
    sampleindexer.h \
    peak_detector.h \
    fft_builder.h \
    fft_hist.h \
    FFTDFT.h \
    FFTWrapper.h \
    qcustomplot.h \
    ftmarker.h \
    fft_filter.h \
    signaldetector.h \
    signalsource.h \
    fxpt.h \
    signalstreamscanner.h \
    signaltablemagextractor.h \
    sinetable.h \
    fxpt_nco.h \
    srifile.h \
    feature_detector.h \
    burst_detector.h \
    file_resampler.h \
    cnpy.h \
    iq_16t.h \
    classifier.h \
    data_exporter.h \
    iplugininterface.h \
    pluginmanager.h \
    iqdemodplayer.h \
    resampler_ff.h \
    datarange.h \
    resampler_arb.h \
    sigtuner.h \
    ftmarker_gui.h \
    sigtuner_gui.h \
    utils.h \
    wgt_util.h \
    qvrt_gps_reader.h \
    fft_hist2.h \
    pluginbase.h

DISTFILES += \
    notes.txt


