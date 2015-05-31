#-------------------------------------------------
#
# Project created by QtCreator 2015-05-28T02:22:49
#
#-------------------------------------------------
include( $${PWD}/../examples.pri )
QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = BatteryMonitor
TEMPLATE = app


SOURCES +=\
    batteryMonitor.cpp \
    cockpitgrid.cpp \
    voltagemeter.cpp

HEADERS  += \
    cockpitgrid.h \
    voltagemeter.h

INCLUDEPATH +=~/src/simplemqttclient/src
LIBS += -lpaho-mqtt3c
LIBS += -L ~/src/simplemqttclient/lib -lsmqtt
