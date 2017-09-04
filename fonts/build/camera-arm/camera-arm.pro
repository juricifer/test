TEMPLATE = app
DESTDIR = ../../lib/arm

# 告诉qmake关于应用程序的配置信息
CONFIG += qt \
    warn_on \
    debug_and_release

# qt库
QT += core \
    gui

DEFINES += USE_SERVICE

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
PLATFORM_PATH = /media/work/sv-g4-application/platform-sdk/arm
HEADERS += ../../src/SVPCameraApp.h \
    ../../src/SVPCameraDlg.h
SOURCES += ../../src/SVPCameraApp.cpp \
    ../../src/SVPCameraDlg.cpp \
    $${PLATFORM_PATH}/include/ui/UI/SVPBaseCtrlFactory.cpp \
    $${PLATFORM_PATH}/include/ui/UI/SVPView.cpp
    
INCLUDEPATH += $${PLATFORM_PATH}/include \
    $${PLATFORM_PATH}/include/ui/UI \
    $${PLATFORM_PATH}/include/ui/GeneralCtrl \
    $${PLATFORM_PATH}/include/3rd 
LIBS += -L$${PLATFORM_PATH}/lib \
    -lappbase \
    -lapp \
	-lservice \
	-lpower \
	-lmedia \
    -lpersist \
    -ltranslator \
    -luiqueued \
    -lcamera \
    -lsource \
    -lRCF \
    -lbasic \
    -lpthread
