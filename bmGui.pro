#-------------------------------------------------
#
# Project created by QtCreator 2015-05-28T02:22:49
#
#-------------------------------------------------
QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = bmGui
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
LIBS += -lqwt-qt5


INCLUDEPATH += /usr/include/qwt

DISTFILES += \
    README.md

