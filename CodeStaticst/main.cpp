#include "codestatisticswindow.h"
#include <QApplication>

#include <windows.h>
#include <QDebug>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    SYSTEM_INFO info;
    GetSystemInfo( &info );;
    qDebug()<<info.dwNumberOfProcessors;
    qDebug()<<info.dwProcessorType;

    CodeStatisticsWindow w;
    w.show();

    return a.exec();
}
