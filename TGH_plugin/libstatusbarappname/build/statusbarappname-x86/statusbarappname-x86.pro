ARCH = x86
PLATFORM_PATH = /media/work/sv-g4-platform

# 生成可执行程序
TEMPLATE = lib

# qt库
QT += core \
    gui

# moc文件存放路径
MOC_DIR += temp

# 放置可执行程序目标的目录
DESTDIR = ../../../$${ARCH}

# 告诉qmake关于应用程序的配置信息
CONFIG += qt \
    warn_on \
    debug_and_release

# 目标名称和中间文件存放路径
CONFIG(release, debug|release) { 
    TARGET = statusbarappname # 指定生成的应用程序名
    OBJECTS_DIR = temp/release # 指定目标文件(obj)的存放目录
}
else { 
    TARGET = statusbarappname_d # 指定生成的应用程序名
    OBJECTS_DIR = temp/debug # 指定目标文件(obj)的存放目录
}

# 应用程序中的所有头文件的列表
HEADERS += ../../src/SVPPluginAppName.h \
    $${PLATFORM_PATH}/ui/include/UI/CtrlPkgInter.h \
    $${PLATFORM_PATH}/ui/include/UI/SVPBaseCtrl.h \
    $${PLATFORM_PATH}/ui/include/UI/SVPBaseCtrlFactory.h \
    $${PLATFORM_PATH}/ui/include/UI/SVPBitmapRes.h \
    $${PLATFORM_PATH}/ui/include/UI/SVPCtrlPkgLib.h \
    $${PLATFORM_PATH}/ui/include/UI/SVPCtrlPtr.h \
    $${PLATFORM_PATH}/ui/include/UI/SVPLibMgr.h \
    $${PLATFORM_PATH}/ui/include/UI/SVPUICore.h \
    $${PLATFORM_PATH}/ui/include/UI/SVPUIObject.h \
    $${PLATFORM_PATH}/ui/include/UI/SVPUIService.h \
    $${PLATFORM_PATH}/ui/include/UI/SVPView.h \
    $${PLATFORM_PATH}/ui/include/UI/UICoreInter.h \
    $${PLATFORM_PATH}/ui/include/UI/UIServiceInter.h \
    $${PLATFORM_PATH}/ui/include/GeneralCtrl/GeneralCtrlPkgInter.h \
    $${PLATFORM_PATH}/ui/include/GeneralCtrl/GeneralCtrlPtr.h

# 应用程序中的所有源文件的列表
SOURCES += ../../src/SVPPluginAppName.cpp \
    ../../src/main.cpp \
    $${PLATFORM_PATH}/ui/include/UI/SVPBaseCtrl.cpp \
    $${PLATFORM_PATH}/ui/include/UI/SVPBaseCtrlFactory.cpp \
    $${PLATFORM_PATH}/ui/include/UI/SVPView.cpp

# 应用程序中的所有.ui文件（由Qt设计器生成）的列表
FORMS += 
RESOURCES += 

# 应用程序所需的额外的包含路径的列表（include文件路径列表）
INCLUDEPATH += ../../include/export \
    ../../src \
    $${PLATFORM_PATH}/system-app/plugins/libpluginbase/include/export \
    $${PLATFORM_PATH}/common/basic \
    $${PLATFORM_PATH}/service/include \
    $${PLATFORM_PATH}/ui/include/GeneralCtrl \
    $${PLATFORM_PATH}/ui/include/UI

# 应用程序所需的额外的预处理程序定义的列表
DEFINES += __LINUX__ \
    __linux__ \
    SVP_SIMULATOR

# -L：引入路径 -l：引入lib(不含后缀)
LIBS += -L../../lib/$${ARCH} \
    -L$${PLATFORM_PATH}/output/$${ARCH}/lib \
    -lservice \
    -lbasic \
    -lpluginbase \
    -lRCF \
    -lapp \
    -luiqueued
