/******************************************************************************************************//**
 *  @file       filecodestatthread.cpp
 *  @brief      文件代码扫描线程 源文件
 *
 *              启动多线程扫描文件 统计代码
 *  @author     coolweedman
 *  @version    V1.00
 *  @date       2016-7-18
 *********************************************************************************************************/

#include "filecodestatthread.h"
#include "filecodestatistics.h"
#include <QStringList>
#include <QDebug>
#include <QCoreApplication>
#include <QMutexLocker>


/**
 *  @fn     CFileCodeStatThread::CFileCodeStatThread(int iId)
 *  @brief  文件代码扫描线程 构造函数
 *  @param  [in] iId    线程ID
 *  @return 无
 */
CFileCodeStatThread::CFileCodeStatThread(int iId)
{
    miThreadId  = iId;
    bFinishFlag = true;

    mphFileCodeStat = new CFileCodeStatistics();
}



/**
 *  @fn     CFileCodeStatThread::~CFileCodeStatThread(int iId)
 *  @brief  文件代码扫描线程 析构函数
 *  @return 无
 */
CFileCodeStatThread::~CFileCodeStatThread(void)
{
    delete mphFileCodeStat;
}



/**
 *  @fn     CFileCodeStatThread::fileCodeStatFileNameSet(QString strFullFileName)
 *  @brief  文件代码扫描线程 设置文件名
 *  @param  [in] strFullFileName    文件名
 *  @return 无
 */
void CFileCodeStatThread::fileCodeStatFileNameSet(QString strFullFileName)
{
    QMutexLocker lock(&mMutex);

    bFinishFlag      = false;
    mstrFullFileName = strFullFileName;

    QStringList strList = strFullFileName.split( "/" );
    mstrFileName = strList.at( strList.length()-1 );
}



/**
 *  @fn     CFileCodeStatThread::run(void)
 *  @brief  文件代码扫描线程 多线程运行
 *  @return 无
 */
void CFileCodeStatThread::run(void)
{
    while (1) {
        if ( bFinishFlag ) {
            QCoreApplication::processEvents();
        } else {
            QMutexLocker lock(&mMutex);

            mphFileCodeStat->fcsFileScan( mstrFullFileName );
            mphFileCodeStat->fcsResGet( msCodeStatResult );

            bFinishFlag = true;

            emit fileCodeDoneSig( miThreadId, mstrFileName, &msCodeStatResult );
        }
    }
}


/**********************************************************************************************************
  END FILE
**********************************************************************************************************/
