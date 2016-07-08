/******************************************************************************************************//**
 *  @file       codestatistics.cpp
 *  @brief      目录代码递归统计 源文件
 *
 *              递归扫描自定目录, 过滤后缀名, 获取文件名
 *              统计有效代码行数/注释行/空行/总行数
 *  @author     CaiWeiMou
 *  @version    V1.00
 *  @date       2016-7-8
 *
 *  @note       Guangzhou ZLGMCU Technology Co., LTD
 *
 *  @par
 *      广州周立功单片机科技有限公司所提供的所有服务内容旨在协助客户加速产品的研发进度，在服务过程中所提供
 *  的任何程序、文档、测试结果、方案、支持等资料和信息，都仅供参考，客户有权不使用或自行参考修改，本公司不
 *  提供任何的完整性、可靠性等保证，若在客户使用过程中因任何原因造成的特别的、偶然的或间接的损失，本公司不
 *  承担任何责任。
 *                                                                        ——广州周立功单片机科技有限公司
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
    phDirScan->dirFileFilterScan( strDir );

    QVector<QString> listFileName;
    phDirScan->dirFileScanedGet( listFileName );

    for ( int i=0; i<listFileName.length(); i++ ) {
        CFileCodeStatistics fileCodeStat( listFileName.at(i) );
        fileCodeStat.fcsFileScan();

        SCodeStatResultStru sStru;
        fileCodeStat.fcsResGet( sStru );

        QPair<QString, SCodeStatResultStru> pairFileStat;
        pairFileStat.first  = listFileName.at(i);
        pairFileStat.second = sStru;

        mvecPairCodeStatResult->push_back( pairFileStat );
    }
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
