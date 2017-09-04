TEMPLATE = app
DESTDIR = ../../lib/x86

# DEFINES += USE_RCF
# 告诉qmake关于应用程序的配置信息
CONFIG += qt \
    warn_on \
    debug_and_release

# qt库
QT += core \
    gui

# moc文件存放路径
MOC_DIR += temp
CONFIG(release, debug|release) { # 如果CONFIG同时配置了debug和release版本，则以release为active选项
    OBJECTS_DIR = temp/release # 指定目标文件(obj)的存放目录
    TARGET = camera # 指定生成的应用程序名
}
else { 
    OBJECTS_DIR = temp/debug # 指定目标文件(obj)的存放目录
    TARGET = camera_d # 指定生成的应用程序名
}
PLATFORM_PATH = /media/work/sv-g4-application/platform-sdk/x86
HEADERS += ../../src/SVPCameraPictureID.h \
    ../../src/SVPCameraPictureID.h \
    ../../src/SVPCameraDlg.h \
    ../../src/SVPCameraApp.h
SOURCES += ../../src/SVPCameraDlg.cpp \
    ../../src/SVPCameraApp.cpp \ # $${PLATFORM_PATH}/include/ui/UI/SVPBaseCtrl.cpp \
    $${PLATFORM_PATH}/include/ui/UI/SVPBaseCtrlFactory.cpp \
    $${PLATFORM_PATH}/include/ui/UI/SVPView.cpp
INCLUDEPATH += $${PLATFORM_PATH}/include \
    $${PLATFORM_PATH}/include/ui/UI \
    $${PLATFORM_PATH}/include/ui/GeneralCtrl \
    $${PLATFORM_PATH}/include/3rd 
LIBS += -L$${PLATFORM_PATH}/lib \
    -lRCF \
    -lappbase \
    -lapp \
    -lservice \
    -lmedia \
    -lpersist \
    -ltranslator \
    -luiqueued \
    -lcamera \
    -lsource \
    -lbasic \
    -lpthread
