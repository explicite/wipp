#-------------------------------------------------
#
# Project created by QtCreator 2013-08-09T21:07:23
#
#-------------------------------------------------

CONFIG += c++11

QMAKE_CXXFLAGS+= -openmp
QMAKE_LFLAGS +=  -openmp

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT +=  widgets printsupport

TARGET = wipp
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    qcustomplot.cpp \
    parser.cpp \
    tab.cpp \
    kolmogorovzurbenko.cpp \
    gwo.cpp \
    function.cpp

HEADERS  += mainwindow.h \
    qcustomplot.h \
    parser.h \
    tab.h \
    kolmogorovzurbenko.h \
    gwo.h \
    function.h \
    optimum.h

FORMS    += mainwindow.ui
