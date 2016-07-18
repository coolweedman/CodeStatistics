/******************************************************************************************************//**
 *  @file       cpuinfo.cpp
 *  @brief      CPU核心数 源文件
 *  @author     coolweedman
 *  @version    V1.00
 *  @date       2016-7-18
 *********************************************************************************************************/

#include "cpuinfo.h"
#include <windows.h>
#include <QDebug>

/**
 *  @fn     cpuProcessorNumGet(void)
 *  @brief  获取CPU核心数
 *  @return CPU核心数
 */
int cpuProcessorNumGet(void)
{
    SYSTEM_INFO info;
    GetSystemInfo( &info );;
    qDebug()<<"CPU Processors "<<info.dwNumberOfProcessors;
    qDebug()<<"CPU Type       "<<info.dwProcessorType;

    return info.dwNumberOfProcessors;
}



/**********************************************************************************************************
  END FILE
**********************************************************************************************************/
