PLATFORM_PATH = /media/work/sv-g4-application/platform-sdk/arm 

# 生成可执行程序
TEMPLATE = lib

# qt库
QT += core \
    gui

# 放置可执行程序目标的目录
DESTDIR = ../../../arm

# 告诉qmake关于应用程序的配置信息
CONFIG += qt \
    warn_on \
    debug_and_release

# 目标名称和中间文件存放路径
MOC_DIR += temp
CONFIG(release, debug|release) {   
    OBJECTS_DIR = temp/release # 指定目标文件(obj)的存放目录
     TARGET = volumeshow # 指定生成的应用程序名
}
else {   
    OBJECTS_DIR = temp/debug # 指定目标文件(obj)的存放目录
    TARGET = volumeshow_d # 指定生成的应用程序名
}

# 应用程序中的所有头文件的列表
HEADERS += ../../src/SVPVolumeShowPic.h \
    ../../src/SVPVolumeShowCtrl.h \
    $${PLATFORM_PATH}/include/ui/UI/CtrlPkgInter.h \
    $${PLATFORM_PATH}/include/ui/UI/SVPBaseCtrl.h \
    $${PLATFORM_PATH}/include/ui/UI/SVPBaseCtrlFactory.h \
    $${PLATFORM_PATH}/include/ui/UI/SVPBitmapRes.h \
    $${PLATFORM_PATH}/include/ui/UI/SVPCtrlPkgLib.h \
    $${PLATFORM_PATH}/include/ui/UI/SVPCtrlPtr.h \
    $${PLATFORM_PATH}/include/ui/UI/SVPLibMgr.h \
    $${PLATFORM_PATH}/include/ui/UI/SVPUICore.h \
    $${PLATFORM_PATH}/include/ui/UI/SVPUIObject.h \
    $${PLATFORM_PATH}/include/ui/UI/SVPUIService.h \
    $${PLATFORM_PATH}/include/ui/UI/SVPView.h \
    $${PLATFORM_PATH}/include/ui/UI/UICoreInter.h \
    $${PLATFORM_PATH}/include/ui/UI/UIServiceInter.h \
    $${PLATFORM_PATH}/include/ui/GeneralCtrl/GeneralCtrlPkgInter.h \
    $${PLATFORM_PATH}/include/ui/GeneralCtrl/GeneralCtrlPtr.h

# 应用程序中的所有源文件的列表
SOURCES += ../../src/SVPVolumeShowCtrl.cpp \
    $${PLATFORM_PATH}/include/ui/UI/SVPBaseCtrl.cpp \
    $${PLATFORM_PATH}/include/ui/UI/SVPBaseCtrlFactory.cpp \
    $${PLATFORM_PATH}/include/ui/UI/SVPView.cpp

# 应用程序中的所有.ui文件（由Qt设计器生成）的列表
FORMS += 
RESOURCES += 

# 应用程序所需的额外的包含路径的列表（include文件路径列表）
INCLUDEPATH += ../../src \
    $${PLATFORM_PATH}/include \
    $${PLATFORM_PATH}/include/ui/GeneralCtrl \
    $${PLATFORM_PATH}/include/ui/UI \
    /media/work/sv-g4-platform/system-app/plugins/libpluginbase/include/export
    
LIBS += -L$${PLATFORM_PATH}/lib \
	-lservice \
    -laudio \
    -lpluginbase \ 
    -lbasic \
    -luiqueued \
    -lpthread  \
    -lsource 