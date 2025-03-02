TARGET = Analyst.gui
TEMPLATE = app

QT += core gui network printsupport widgets
CONFIG += c++14

include (../../libsdrkit/libsdrkit.pri)
include (../../qvrt_lib/qvrt_util/qvrt_util.pri)

DEFINES += QCUSTOMPLOT_USE_OPENGL

INCLUDEPATH += /usr/local/include
INCLUDEPATH += $$OUT_PWD
INCLUDEPATH += /opt/intel/ipp/include

LIBS += -L/usr/local/lib
LIBS += -L/opt/intel/compilers_and_libraries_2017.4.196/linux/ipp/lib/intel64/
LIBS += -lboost_system -lfftw3f -lz
LIBS += -lopencv_core -lopencv_imgproc -lopencv_highgui -lasound -lopencv_photo # openCV

#LIBS += -lmarblewidget-qt5 # marble mapping
LIBS += -lliquid


SOURCES += main.cpp\
    dlgsignaldetector.cpp \
    dlgstreamoptions.cpp \
    mainwindow.cpp \
    ctkRangeSlider.cpp \
    dlgprogress.cpp \
    frmimportoptions.cpp \
    wgt_marker_editor.cpp \
    wgt_timeeditor.cpp \
    wgtclassifier.cpp \
    dlgnewclassifier.cpp \
    wgt_scope.cpp \
    wgt_sig_base.cpp \
    wgt_fft.cpp \
    wgt_waterfall.cpp \
    audio_util.cpp \
    wgt_marker_table.cpp

HEADERS  += mainwindow.h \
    ctkPimpl.h \
    ctkRangeSlider.h \
    dlgprogress.h \
    dlgsignaldetector.h \
    dlgstreamoptions.h \
    frmimportoptions.h \
    wgt_marker_editor.h \
    wgt_timeeditor.h \
    wgtclassifier.h \
    dlgnewclassifier.h \
    wgt_scope.h \
    wgt_sig_base.h \
    wgt_fft.h \
    wgt_waterfall.h \
    audio_util.h \
    wgt_marker_table.h

FORMS    += mainwindow.ui \
    dlgsignaldetector.ui \
    dlgstreamoptions.ui \
    frmimportoptions.ui \
    dlgprogress.ui \
    wgt_marker_editor.ui \
    wgt_timeeditor.ui \
    wgtclassifier.ui \
    dlgnewclassifier.ui \
    wgt_scope.ui \
    wgt_fft.ui \
    wgt_waterfall.ui \
    wgt_marker_table.ui



DISTFILES += \
    Notes.txt \
    dependencies.txt

RESOURCES += \
    icons.qrc



##----------------CUDA Stuff
... # QT, SOURCES, HEADERS, the usual stuff

CUDA_DIR = /usr/local/cuda-10.2/

exists( $$CUDA_DIR ) {
      message( "CUDA detected" )
#CUDA_SOURCES += \
#    vectorAdd.cu
    CUDA_SOURCES += #vectorAdd.cu

    DEFINES += USE_CUDA
    CUDA_ARCH = sm_32 # as supported by the Tegra K1
    INCLUDEPATH += $$CUDA_DIR/include
    LIBS += -L $$CUDA_DIR/lib64 -lcudart -lcuda -lcufft # path needs to be changed for different architectures

    cuda.commands = $$CUDA_DIR/bin/nvcc -c -arch=$$CUDA_ARCH  -o ${QMAKE_FILE_OUT} ${QMAKE_FILE_NAME}
    cuda.dependency_type = TYPE_C
    cuda.depend_command = $$CUDA_DIR/bin/nvcc -M ${QMAKE_FILE_NAME}
    cuda.input = CUDA_SOURCES
    cuda.output = ${QMAKE_FILE_BASE}_cuda.o
    QMAKE_EXTRA_COMPILERS += cuda
}

