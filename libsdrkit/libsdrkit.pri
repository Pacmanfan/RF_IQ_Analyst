
CONFIG += c++14

INCLUDEPATH += $$PWD

LIB_PATH = $$relative_path($$PWD, $$_PRO_FILE_PWD_)

LIBS += -L$$OUT_PWD/$$LIB_PATH/ -lsdrkit
PRE_TARGETDEPS += $$OUT_PWD/$$LIB_PATH/libsdrkit.a

