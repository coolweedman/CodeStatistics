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
    ../Code/App/filecodestatistics.cpp \
    ../Code/App/dirscanstatistics.cpp \
    ../Code/App/codestatistics.cpp \
    ../Code/Ui/codestatisticswindow.cpp

HEADERS  += \
    ../Code/Comm/typedefs.h \
    ../Code/App/filecodestatistics.h \
    ../Code/App/dirscanstatistics.h \
    ../Code/App/codestatistics.h \
    ../Code/Ui/codestatisticswindow.h

FORMS    += \
    ../Code/Ui/codestatisticswindow.ui

INCLUDEPATH += ../Code/Comm
INCLUDEPATH += ../Code/App
INCLUDEPATH += ../Code/Ui
