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
    forger.cpp \
    readPcap.cpp

HEADERS  += \
    capture.h \
    ethernetprotocol.h \
    interfaces.h \
    internetprotocol.h \
    mainwindow.h \
    mypacket.h \
    forger.h \
    readPcap.h

FORMS += \
    mainwindow.ui

OTHER_FILES += \
    sniffer.pro.user

unix:!macx: LIBS += -L$$PWD/../../../../usr/local/lib/ -lpcap

INCLUDEPATH += $$PWD/../../../../usr/local/include
DEPENDPATH += $$PWD/../../../../usr/local/include
=======
    ethernetprotocol.h \
    forger.h
>>>>>>> 4a05d04864153d503682191d2b2b3e3b9d16f297

unix:!macx: PRE_TARGETDEPS += $$PWD/../../../../usr/local/lib/libpcap.a
