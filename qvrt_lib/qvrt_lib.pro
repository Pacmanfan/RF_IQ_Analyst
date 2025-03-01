
_JENKINSBUILD = $$(JENKINSBUILD) # set the local var so it can be used

isEmpty(_JENKINSBUILD) {
    #message("Jenkins build flag not detected. Setting up for subdirs")
    win32:TEMPLATE = subdirs
    else: TEMPLATE = subdirs

}else {
    #message("Jenkins build flag  detected, setting vcsubdirs")
    win32:TEMPLATE = vcsubdirs
    else: TEMPLATE = subdirs
}
#win32:TEMPLATE = vcsubdirs
#else: TEMPLATE = subdirs
#qvrt_util.file = ../qvrt_util/qvrt_util.pro

#qvrt_test.depends += qvrt_util

SUBDIRS = \
    qvrt_util
    qvrt_test
