#-------------------------------------------------
#
# Project created by QtCreator 2013-08-09T21:07:23
#
#-------------------------------------------------

CONFIG += c++11

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT +=  widgets printsupport

TARGET = wipp
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    qcustomplot.cpp \
    parser.cpp \
    tab.cpp \
    kolmogorovzurbenko.cpp

HEADERS  += mainwindow.h \
    qcustomplot.h \
    parser.h \
    tab.h \
    kolmogorovzurbenko.h

FORMS    += mainwindow.ui
