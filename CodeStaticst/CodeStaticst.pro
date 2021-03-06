#-------------------------------------------------
#
# Project created by QtCreator 2016-07-06T16:01:35
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CodeStaticst
TEMPLATE = app

TRANSLATIONS = CodeStatistics.ts

RC_FILE += ../Resource/icon.rc

SOURCES += main.cpp\
    ../Code/App/filecodestatistics.cpp \
    ../Code/App/dirscanstatistics.cpp \
    ../Code/App/codestatistics.cpp \
    ../Code/Ui/codestatisticswindow.cpp \
    ../Code/Ui/filefilterwindow.cpp \
    ../Code/Thread/filecodestatthread.cpp \
    ../Code/Thread/cpuinfo.cpp \
    ../Code/App/qpplanguage.cpp

HEADERS  += \
    ../Code/Comm/typedefs.h \
    ../Code/App/filecodestatistics.h \
    ../Code/App/dirscanstatistics.h \
    ../Code/App/codestatistics.h \
    ../Code/Ui/codestatisticswindow.h \
    ../Code/Ui/filefilterwindow.h \
    ../Code/Thread/filecodestatthread.h \
    ../Code/Thread/cpuinfo.h \
    ../Code/App/applanguage.h

FORMS    += \
    ../Code/Ui/codestatisticswindow.ui \
    ../Code/Ui/filefilterwindow.ui

INCLUDEPATH += ../Code/Comm
INCLUDEPATH += ../Code/App
INCLUDEPATH += ../Code/Ui
INCLUDEPATH += ../Code/Thread
