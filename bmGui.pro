#-------------------------------------------------
#
# Project created by QtCreator 2015-05-28T02:22:49
#
#-------------------------------------------------
include( $${PWD}/../examples.pri )
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
    graphview.cpp

HEADERS  += \
    cockpitgrid.h \
    voltagemeter.h \
    batterydata.h \
    utils.h \
    currentmeter.h \
    graphview.h
DEFINES += QT_MESSAGELOGCONTEXT

LIBS +=-L/usr/local/lib -lsmqtt
LIBS += -lpaho-mqtt3c


