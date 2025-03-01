
CONFIG += c++14

INCLUDEPATH += $$PWD
INCLUDEPATH += $$PWD/include

LIB_PATH = $$relative_path($$PWD, $$_PRO_FILE_PWD_)


unix{
    LIBS += -L$$OUT_PWD/$$LIB_PATH/ -lqvrt_util
    PRE_TARGETDEPS += $$OUT_PWD/$$LIB_PATH/libqvrt_util.a
}

win32{
    Release: PRE_TARGETDEPS += $$OUT_PWD/$$LIB_PATH/release/qvrt_util.lib
    Debug: PRE_TARGETDEPS += $$OUT_PWD/$$LIB_PATH/debug/qvrt_util.lib
    Release: LIBS += -L$$OUT_PWD/$$LIB_PATH/release/ -lqvrt_util
    Debug: LIBS += -L$$OUT_PWD/$$LIB_PATH/debug/ -lqvrt_util
}
