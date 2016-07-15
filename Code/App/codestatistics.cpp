/******************************************************************************************************//**
 *  @file       codestatistics.cpp
 *  @brief      目录代码递归统计 源文件
 *
 *              递归扫描自定目录, 过滤后缀名, 获取文件名
 *              统计有效代码行数/注释行/空行/总行数
 *  @author     coolweedman
 *  @version    V1.00
 *  @date       2016-7-8
 *********************************************************************************************************/

#include "codestatistics.h"
#include <QVector>
#include <QString>
#include <QPair>
#include <QDebug>
#include "filecodestatthread.h"
#include <QMetaType>
#include <string.h>
#include <QMutexLocker>
#include <QMutex>

/**
 *  @fn     CCodeStatistics::CCodeStatistics(void)
 *  @brief  目录代码递归统计 构造函数
 *  @return 无
 */
CCodeStatistics::CCodeStatistics(void)
{
    mvecPairCodeStatResult = new QVector< QPair<QString, SCodeStatResultStru> >();

    mpStrListFilter    = new QStringList();
    mpListFileFullName = new QVector<QString>();
    mpListFileName     = new QVector<QString>();

    mbFinishFlag = true;

    mpFileCodeStatHandler = new QVector<CFileCodeStatThread *>();

    codeStatThreadCreate();
}



/**
 *  @fn     CCodeStatistics::~CCodeStatistics(void)
 *  @brief  目录代码递归统计 析构函数
 *  @return 无
 */
CCodeStatistics::~CCodeStatistics(void)
{
    delete mvecPairCodeStatResult;
    delete mpStrListFilter;
    delete mpListFileFullName;
    delete mpListFileName;

    for ( int i=0; i<mpFileCodeStatHandler->length(); i++ ) {
        delete mpFileCodeStatHandler->at(i);
    }
}


void CCodeStatistics::codeStatFileGet(QString strDir)
{
    CDirScanStatistics *phDirScan = new CDirScanStatistics();

    phDirScan->dirFileFilterSet( *mpStrListFilter );
    phDirScan->dirFileFilterScan( strDir );

    mpListFileFullName->clear();
    phDirScan->dirFileFullNameGet( *mpListFileFullName );
    mulDoneCnt = mpListFileFullName->length();

    mpListFileName->clear();
    phDirScan->dirFileNameGet( *mpListFileName );

    qDebug()<<"File "<<mpListFileName->length();
}


void CCodeStatistics::codeStatOneFileStart(int iId)
{
    QString strFileName;
    strFileName = mpListFileFullName->front();
    mpListFileFullName->pop_front();

    mpFileCodeStatHandler->at(iId)->fileCodeStatFileNameSet( strFileName );
    mpFileCodeStatHandler->at(iId)->start();
}


void CCodeStatistics::codeStatOneFileDoneProc(int iId, QString strFileNmae, const SCodeStatResultStru *psCodeStatResult)
{
    QPair<QString, SCodeStatResultStru> pairFileStat;
    pairFileStat.first  = strFileNmae;
    memcpy( &pairFileStat.second, psCodeStatResult, sizeof(SCodeStatResultStru) );

    mvecPairCodeStatResult->push_back( pairFileStat );
    mulDoneCnt--;

    if ( mpListFileFullName->length() > 0 ) {
        emit codeStatProgressSig( mvecPairCodeStatResult->length(), mpListFileFullName->length() + mvecPairCodeStatResult->length() + 1 );
        codeStatOneFileStart( iId );
    } else if ( 0 == mulDoneCnt ) {
        codeStatThreadStop();
        emit codeStatDoneSig();
    }
}



void CCodeStatistics::codeStatThreadCreate(void)
{
    qRegisterMetaType<SCodeStatResultStru>("SCodeStatResultStru");

    for ( int i=0; i<2; i++ ) {
        mpFileCodeStatHandler->push_back( new CFileCodeStatThread(i) );

        connect( mpFileCodeStatHandler->at(i),
                 SIGNAL(fileCodeDoneSig(int,QString,const SCodeStatResultStru *)),
                 this,
                 SLOT(codeStatOneFileDoneProc(int,QString,const SCodeStatResultStru *)) );
    }
}

void CCodeStatistics::codeStatThreadStop(void)
{
    for ( int i=0; i<mpFileCodeStatHandler->length() ; i++ ) {
        mpFileCodeStatHandler->at(i)->terminate();
    }
}


/**
 *  @fn     CCodeStatistics::codeStatProc(QString strDir)
 *  @brief  目录代码递归统计 统计
 *  @param  [in] strDir 扫描目录
 *  @return 无
 */
void CCodeStatistics::codeStatProc(QString strDir)
{
#if 1
    mbFinishFlag = false;

    codeStatFileGet( strDir );

    mvecPairCodeStatResult->clear();

    for ( int i=0; i<mpFileCodeStatHandler->length(); i++ ) {
        codeStatOneFileStart( i );
    }
#else
    for ( int i=0; i<mpListFileFullName->length(); i++ ) {
        CFileCodeStatistics fileCodeStat;
        fileCodeStat.fcsFileScan( mpListFileFullName->at(i) );

        SCodeStatResultStru sStru;
        fileCodeStat.fcsResGet( sStru );

        QPair<QString, SCodeStatResultStru> pairFileStat;
        pairFileStat.first  = mpListFileName->at(i);
        pairFileStat.second = sStru;

        mvecPairCodeStatResult->push_back( pairFileStat );

        emit codeStatProgressSig( i, mpListFileFullName->length() );
    }

    emit codeStatDoneSig();
#endif
}



/**
 *  @fn     CCodeStatistics::codeStatResGet(SCodeStatResultStru &sResStru)
 *  @brief  目录代码递归统计 结果获取
 *  @param  [out] sResStru  结果结构体
 *  @return 无
 */
void CCodeStatistics::codeStatResGet(SCodeStatResultStru &sResStru)
{
    sResStru.uiEffeCodeLines    = 0;
    sResStru.uiCommentCodeLines = 0;
    sResStru.uiEmptyLineNum     = 0;
    sResStru.uiTotalLineNum     = 0;

    for ( int i=0; i<mvecPairCodeStatResult->length(); i++ ) {
        sResStru.uiEffeCodeLines    += mvecPairCodeStatResult->at(i).second.uiEffeCodeLines;
        sResStru.uiCommentCodeLines += mvecPairCodeStatResult->at(i).second.uiCommentCodeLines;
        sResStru.uiEmptyLineNum     += mvecPairCodeStatResult->at(i).second.uiEmptyLineNum;
        sResStru.uiTotalLineNum     += mvecPairCodeStatResult->at(i).second.uiTotalLineNum;
    }
}


void CCodeStatistics::codeStatFilterSet(QStringList &rListStrFilter)
{
    mpStrListFilter->clear();

    for ( int i=0; i<rListStrFilter.length(); i++ ) {
        mpStrListFilter->push_back( rListStrFilter.at(i) );
    }
}


/**
 *  @fn     CCodeStatistics::codeStatDetailResGet(QVector<QPair<QString, SCodeStatResultStru> > &rVecPair)
 *  @brief  目录代码递归统计 详细结果获取
 *  @param  [out] rVecPair  详细结果结构体
 *  @return 无
 */
void CCodeStatistics::codeStatDetailResGet(QVector<QPair<QString, SCodeStatResultStru> > &rVecPair)
{
    rVecPair.clear();

    for ( int i=0; i<mvecPairCodeStatResult->length(); i++ ) {
        rVecPair.push_back( mvecPairCodeStatResult->at(i) );
    }
}



/**
 *  @fn     CCodeStatistics::codeStatResPrint(SCodeStatResultStru &sResStru)
 *  @brief  目录代码递归统计 结果打印
 *  @param  [in] sResStru  结果结构体
 *  @return 无
 */
void CCodeStatistics::codeStatResPrint(SCodeStatResultStru &sResStru)
{
    qDebug()<<"****** Total ******";
    qDebug()<<"Effe    Line "<<sResStru.uiEffeCodeLines;
    qDebug()<<"Comment Line "<<sResStru.uiCommentCodeLines;
    qDebug()<<"Empyt   Line "<<sResStru.uiEmptyLineNum;
    qDebug()<<"Total   Line "<<sResStru.uiTotalLineNum;
    qDebug()<<"******       ******";
}



/**
 *  @fn     CCodeStatistics::codeStatDetailResPrint(QVector<QPair<QString, SCodeStatResultStru> > &rVecPair)
 *  @brief  目录代码递归统计 详细结果打印
 *  @param  [out] rVecPair  详细结果结构体
 *  @return 无
 */
void CCodeStatistics::codeStatDetailResPrint(QVector<QPair<QString, SCodeStatResultStru> > &rVecPair)
{
    for ( int i=0; i<rVecPair.length(); i++ ) {
        qDebug()<<rVecPair.at(i).first;
        CFileCodeStatistics::fcsResPrint( rVecPair.at(i).second );
        qDebug()<<"";
    }

    qDebug()<<"Total File "<<rVecPair.length();
}



/**********************************************************************************************************
  END FILE
**********************************************************************************************************/
