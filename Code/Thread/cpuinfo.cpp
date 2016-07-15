#include "cpuinfo.h"
#include <windows.h>
#include <QDebug>

int cpuProcessorNumGet(void)
{
    SYSTEM_INFO info;
    GetSystemInfo( &info );;
    qDebug()<<"CPU Processors "<<info.dwNumberOfProcessors;
    qDebug()<<"CPU Type       "<<info.dwProcessorType;

    return info.dwNumberOfProcessors;
}
