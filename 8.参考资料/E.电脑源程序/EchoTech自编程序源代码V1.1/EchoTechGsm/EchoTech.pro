#-------------------------------------------------
#
# Project created by QtCreator 2011-08-09T12:23:14
#
#-------------------------------------------------

QT       += core gui network

TARGET = EchoTech
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    etgsm.cpp \
    win_qextserialport.cpp \
    qextserialbase.cpp

HEADERS  += mainwindow.h \
    etgsm.h \
    win_qextserialport.h \
    qextserialbase.h

FORMS    += mainwindow.ui \
    etgsm.ui
