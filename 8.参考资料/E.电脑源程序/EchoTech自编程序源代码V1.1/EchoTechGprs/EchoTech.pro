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
    etgprs.cpp \
    win_qextserialport.cpp \
    qextserialbase.cpp

HEADERS  += mainwindow.h \
    etgprs.h \
    win_qextserialport.h \
    qextserialbase.h

FORMS    += mainwindow.ui \
    etgprs.ui
