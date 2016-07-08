#-------------------------------------------------
#
# Project created by QtCreator 2016-07-06T16:01:35
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CodeStaticst
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    ../Code/App/filecodestatistics.cpp \
    ../Code/App/dirscanstatistics.cpp \
    ../Code/App/codestatistics.cpp

HEADERS  += mainwindow.h \
    ../Code/Comm/typedefs.h \
    ../Code/App/filecodestatistics.h \
    ../Code/App/dirscanstatistics.h \
    ../Code/App/codestatistics.h

FORMS    += mainwindow.ui

INCLUDEPATH += ../Code/Comm
INCLUDEPATH += ../Code/App
