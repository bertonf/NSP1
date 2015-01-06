#-------------------------------------------------
#
# Project created by QtCreator 2015-01-04T20:11:37
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = sniffer
TEMPLATE = app


SOURCES += main.cpp \
    capture.cpp \
    ethernetprotocol.cpp \
    interfaces.cpp \
    internetprotocol.cpp \
    mainwindow.cpp \
    mypacket.cpp \
    readPcap.cpp

HEADERS  += \
    capture.h \
    ethernetprotocol.h \
    interfaces.h \
    internetprotocol.h \
    mainwindow.h \
    mypacket.h \
    readPcap.h

FORMS += \
    mainwindow.ui

OTHER_FILES += \
    sniffer.pro.user

unix:!macx: LIBS += -L$$PWD/../../../../usr/local/lib/ -lpcap

INCLUDEPATH += $$PWD/../../../../usr/local/include
DEPENDPATH += $$PWD/../../../../usr/local/include

unix:!macx: PRE_TARGETDEPS += $$PWD/../../../../usr/local/lib/libpcap.a
