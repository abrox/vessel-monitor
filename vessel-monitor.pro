#-------------------------------------------------
#
# Project created by QtCreator 2015-05-28T02:22:49
#
#-------------------------------------------------
QT       += core gui
#CONFIG += PC_HOST
greaterThan(QT_MAJOR_VERSION, 4): cache
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = vessel-monitor
TEMPLATE = app


SOURCES +=\
    bmgui.cpp \
    cockpitgrid.cpp \
    voltagemeter.cpp \
    batterydata.cpp \
    currentmeter.cpp \
    graphview.cpp \
    batteryplot.cpp \
    wheelbox.cpp \
    utils.cpp
HEADERS  += \
    cockpitgrid.h \
    voltagemeter.h \
    batterydata.h \
    utils.h \
    currentmeter.h \
    graphview.h \
    batteryplot.h \
    const.h\
    wheelbox.h
DEFINES += QT_MESSAGELOGCONTEXT

LIBS += -lsmqtt
LIBS += -lpaho-mqtt3c

PC_HOST{
  LIBS += -lqwt-qt5
  INCLUDEPATH += /usr/include/qwt
  target.path = /usr/local/bin

}else{
  LIBS += -lqwt
  target.path = /usr/bin
}

INSTALLS += target
INCLUDEPATH += GeneratedFiles

MOC_DIR = GeneratedFiles
OBJECTS_DIR = Objects
UI_DIR = GeneratedFiles
RCC_DIR = GeneratedFiles

DISTFILES += \
    README.md
