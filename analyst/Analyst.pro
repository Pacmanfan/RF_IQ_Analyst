TEMPLATE = subdirs

SUBDIRS = \
    qvrt_util \
    libsdrkit \
    Analyst

#include(AnalystVersion.pri)

###########################################

libsdrkit.subdir = ../libsdrkit
qvrt_util.file = ../qvrt_lib/qvrt_util/qvrt_util.pro

#RESOURCES += \
#    Analyst/images.qrc
