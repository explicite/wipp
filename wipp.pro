CONFIG += c++11

QMAKE_CXXFLAGS  += -fopenmp -std=c++0x
QMAKE_LFLAGS    += -fopenmp -std=c++0x

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT +=  widgets printsupport

TARGET      = wipp
TEMPLATE    = app


SOURCES  += main.cpp \
            mainwindow.cpp \
            qcustomplot.cpp \
            parser.cpp \
            tab.cpp \
            kolmogorovzurbenko.cpp \
            gwo.cpp \
            function.cpp \
            bsplain.cpp

HEADERS  += mainwindow.h \
            qcustomplot.h \
            parser.h \
            tab.h \
            kolmogorovzurbenko.h \
            gwo.h \
            function.h \
            optimum.h \
            bsplain.h

FORMS    += mainwindow.ui
