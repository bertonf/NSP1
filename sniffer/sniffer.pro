#-------------------------------------------------
#
# Project created by QtCreator 2014-10-20T23:13:33
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = sniffer
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    interfaces.cpp \
    capture.cpp \
    internetprotocol.cpp \
    mypacket.cpp \
    ethernetprotocol.cpp

HEADERS  += mainwindow.h \
    interfaces.h \
    capture.h \
    internetprotocol.h \
    mypacket.h \
    ethernetprotocol.h

FORMS    += mainwindow.ui
