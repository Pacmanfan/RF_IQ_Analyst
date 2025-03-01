
TARGET = qvrt_util

_JENKINSBUILD = $$(JENKINSBUILD) # set the local var so it can be used

isEmpty(_JENKINSBUILD) {
    TEMPLATE = lib
}else {
    win32:TEMPLATE = vclib
    else: TEMPLATE = lib
}

CONFIG += staticlib
CONFIG += c++14
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += qvrt_header.cpp \
    qvrt_iqdatapacket.cpp \
    qvrt_packet.cpp \
    qvrt_tool.cpp \
    qvrt_ext_data_packet.cpp \
    qvrt_ifcontext_packet.cpp \
    fixed_t.cpp \
    ExtDataRadioSettings.cpp \
    circbuff.cpp \
    qvrt_reader.cpp \
    qvrt_ext_context_packet.cpp \
    qvrt_writer.cpp \
    qvrt_fileinfo.cpp

LIBS += -lpthread

INCLUDEPATH += .

HEADERS += \
    numpy.i \
    qvrt_tools.h \
    fixed_t.h \
    circbuff.h
