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
        mainwindow.cpp \
    batteryMonitor.cpp

HEADERS  += mainwindow.h
