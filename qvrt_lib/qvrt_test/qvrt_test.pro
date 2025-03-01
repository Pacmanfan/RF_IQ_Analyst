TEMPLATE = app
CONFIG += console
CONFIG -= qt
CONFIG += c++14

SOURCES += \
    main.cpp

#LIBS += -lboost_system -lboost_program_options
#LIBS += -lPocoFoundation -lPocoUtil

OTHER_FILES += \
    Notes.txt

include(../qvrt_util/qvrt_util.pri)
