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



/**
 *  @fn     CCodeStatistics::CCodeStatistics(void)
 *  @brief  目录代码递归统计 构造函数
 *  @return 无
 */
CCodeStatistics::CCodeStatistics(void)
{
    mvecPairCodeStatResult = new QVector< QPair<QString, SCodeStatResultStru> >();
    mpStrListFilter = new QStringList();
}



/**
 *  @fn     CCodeStatistics::~CCodeStatistics(void)
 *  @brief  目录代码递归统计 析构函数
 *  @return 无
 */
CCodeStatistics::~CCodeStatistics(void)
{

}



/**
 *  @fn     CCodeStatistics::codeStatProc(QString strDir)
 *  @brief  目录代码递归统计 统计
 *  @param  [in] strDir 扫描目录
 *  @return 无
 */
void CCodeStatistics::codeStatProc(QString strDir)
{
    CDirScanStatistics *phDirScan = new CDirScanStatistics();
    phDirScan->dirFileFilterSet( *mpStrListFilter );
    phDirScan->dirFileFilterScan( strDir );

    QVector<QString> listFileFullName;
    phDirScan->dirFileScanedGet( listFileFullName );
    QVector<QString> listFileName;
    phDirScan->dirFileNameGet( listFileName );

    for ( int i=0; i<listFileFullName.length(); i++ ) {
        CFileCodeStatistics fileCodeStat;
        fileCodeStat.fcsFileScan( listFileFullName.at(i) );

        SCodeStatResultStru sStru;
        fileCodeStat.fcsResGet( sStru );

        QPair<QString, SCodeStatResultStru> pairFileStat;
        pairFileStat.first  = listFileName.at(i);
        pairFileStat.second = sStru;

        mvecPairCodeStatResult->push_back( pairFileStat );

        emit codeStatProgressSig( i, listFileFullName.length() );
    }

    emit codeStatDoneSig();
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
