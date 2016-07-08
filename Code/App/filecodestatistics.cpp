/******************************************************************************************************//**
 *  @file       filecodestatistics.cpp
 *  @brief      代码统计 源文件
 *
 *              根据文件名, 统计代码
 *              有效代码行/注释行/空行/总行数
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

#include "filecodestatistics.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <string.h>


/**
 *  @fn     CFileCodeStatistics::CFileCodeStatistics(QString strFileName)
 *  @brief  代码统计 构造函数
 *  @param  [in]    strFileName 文件名
 *  @return 无
 */
CFileCodeStatistics::CFileCodeStatistics(QString strFileName)
{
    mpFile = new QFile( strFileName );

    if ( NULL == mpFile ) {
        return;

    }
    if ( !mpFile->open(QIODevice::ReadOnly | QIODevice::Text) ) {
        return;
    }

    fcsStruInit();
}



/**
 *  @fn     CFileCodeStatistics::~CFileCodeStatistics(QString strFileName)
 *  @brief  代码统计 析构函数
 *  @return 无
 */
CFileCodeStatistics::~CFileCodeStatistics(void)
{
    if ( NULL != mpFile ) {
        mpFile->close();
        delete mpFile;
    }
}



/**
 *  @fn     CFileCodeStatistics::fcsFileScan(void)
 *  @brief  代码统计 文件扫描
 *  @return 无
 */
void CFileCodeStatistics::fcsFileScan(void)
{
    QTextStream textStream( mpFile );

    while ( !textStream.atEnd() ) {
        QString strLine = textStream.readLine();

        for ( int i=0; i<strLine.length(); i++ ) {
            fcsFsmCharProc( strLine.at(i).toLatin1() );
        }
        fcsFsmCharProc( '\n' );

        qDebug()<<strLine;
    }
}



/**
 *  @fn     CFileCodeStatistics::fcsResGet(SEcodeStatisticsStru &sStru)
 *  @brief  代码统计 结果获取
 *  @param  [out] sStru 统计结果
 *  @return 无
 */
void CFileCodeStatistics::fcsResGet(SEcodeStatisticsStru &sStru)
{
    memcpy( &sStru, &msCodeStat, sizeof(SEcodeStatisticsStru) );
}



/**
 *  @fn     CFileCodeStatistics::fcsResultPrint(void)
 *  @brief  代码统计 结果打印
 *  @return 无
 */
void CFileCodeStatistics::fcsResultPrint(void)
{
    qDebug()<<"EffeCode Line "<<msCodeStat.uiEffeCodeLines;
    qDebug()<<"Comment  Line "<<msCodeStat.uiCommentCodeLines;
    qDebug()<<"Empty    Line "<<msCodeStat.uiEmptyLineNum;
    qDebug()<<"Total    Line "<<msCodeStat.uiTotalLineNum;
}



/**
 *  @fn     CFileCodeStatistics::fcsStruInit(void)
 *  @brief  代码统计 结构体初始化
 *  @return 无
 */
void CFileCodeStatistics::fcsStruInit(void)
{
    msCodeStat.eCommentStat       = CODECOMMENT_IDLE;

    msCodeStat.bEffeCodeFlag      = false;
    msCodeStat.bEmptyLineFlag     = true;
    msCodeStat.bCommentCodeFlag   = false;

    msCodeStat.uiEffeCodeLines    = 0;
    msCodeStat.uiCommentCodeLines = 0;
    msCodeStat.uiEmptyLineNum     = 0;
    msCodeStat.uiTotalLineNum     = 0;

    msCodeStat.bCommentBlockOutFlag = false;
}



/**
 *  @fn     CFileCodeStatistics::fcsFsmCharProc(char cChr)
 *  @brief  代码统计 字符解码状态机
 *  @param  [in] cChr   解码字符
 *  @return 无
 */
void CFileCodeStatistics::fcsFsmCharProc(char cChr)
{
    if ( '\n' == cChr ) {
        fcsLineInc();
    }

    switch ( msCodeStat.eCommentStat ) {
    case CODECOMMENT_IDLE:
        fcsFsmIdelProc( cChr );
        break;

    case CODECOMMENT_SLASHIN:
        fcsFsmSlashInProc( cChr );
        break;

    case CODECOMMENT_LINEIN:
        fcsFsmLineInProc( cChr );
        break;

    case CODECOMMENT_BOLCKIN:
        fcsFsmBlockInProc( cChr );
        break;

    case CODECOMMENT_SLASHOUT:
        fcsFsmSlashOutProc( cChr );
        break;

    default:
        break;
    }
}



/**
 *  @fn     CFileCodeStatistics::fcsLineInc(void)
 *  @brief  代码统计 累计行数
 *  @return 无
 */
void CFileCodeStatistics::fcsLineInc(void)
{
    if ( msCodeStat.bEffeCodeFlag ) {
        msCodeStat.uiEffeCodeLines++;
    }
    if ( msCodeStat.bCommentCodeFlag ) {
        msCodeStat.uiCommentCodeLines++;
    }
    if ( msCodeStat.bEmptyLineFlag ) {
        msCodeStat.uiEmptyLineNum++;
    }
    if ( msCodeStat.bCommentBlockOutFlag ) {
        msCodeStat.bCommentBlockOutFlag = false;
        if ( !msCodeStat.bCommentCodeFlag ) {
            msCodeStat.uiCommentCodeLines++;
        }
    }

    msCodeStat.uiTotalLineNum++;
}



/**
 *  @fn     CFileCodeStatistics::fcsFsmIdelProc(char cChr)
 *  @brief  代码统计 未确定状态才处理
 *  @param  [in] cChr   解码字符
 *  @return 无
 */
void CFileCodeStatistics::fcsFsmIdelProc(char cChr)
{
    switch ( cChr ) {
    case '/':
        msCodeStat.eCommentStat   = CODECOMMENT_SLASHIN;
        msCodeStat.bEmptyLineFlag = false;
        break;

    case ' ':
    case '\t':
    case '\r':
        break;

    case '\n':
        msCodeStat.bEffeCodeFlag  = false;
        msCodeStat.bEmptyLineFlag = true;
        break;

    default:
        msCodeStat.bEmptyLineFlag = false;
        msCodeStat.bEffeCodeFlag  = true;
        break;
    }
}



/**
 *  @fn     CFileCodeStatistics::fcsFsmSlashInProc(char cChr)
 *  @brief  代码统计 '/'状态处理
 *
 *          检测到'/'后, 等待'/'行注释 '*'块注释
 *  @param  [in] cChr   解码字符
 *  @return 无
 */
void CFileCodeStatistics::fcsFsmSlashInProc(char cChr)
{
    switch ( cChr ) {
    case '/':
        msCodeStat.eCommentStat     = CODECOMMENT_LINEIN;
        msCodeStat.bCommentCodeFlag = true;
        break;

    case '*':
        msCodeStat.eCommentStat     = CODECOMMENT_BOLCKIN;
        msCodeStat.bCommentCodeFlag = true;
        break;

    case '\n':
        msCodeStat.eCommentStat  = CODECOMMENT_IDLE;
        msCodeStat.bEffeCodeFlag = false;
        break;

    default:
        msCodeStat.eCommentStat  = CODECOMMENT_IDLE;
        msCodeStat.bEffeCodeFlag = true;
        break;
    }
}



/**
 *  @fn     CFileCodeStatistics::fcsFsmLineInProc(char cChr)
 *  @brief  代码统计 行注释处理
 *
 *          行注释
 *  @param  [in] cChr   解码字符
 *  @return 无
 */
void CFileCodeStatistics::fcsFsmLineInProc(char cChr)
{
    switch ( cChr ) {
    case '\n':
        msCodeStat.eCommentStat     = CODECOMMENT_IDLE;
        msCodeStat.bCommentCodeFlag = false;
        msCodeStat.bEffeCodeFlag    = false;

        break;

    default:
        break;
    }
}



/**
 *  @fn     CFileCodeStatistics::fcsFsmBlockInProc(char cChr)
 *  @brief  代码统计 块注释处理
 *
 *          块注释内, 等待'*'
 *  @param  [in] cChr   解码字符
 *  @return 无
 */
void CFileCodeStatistics::fcsFsmBlockInProc(char cChr)
{
    switch ( cChr ) {
    case '*':
        msCodeStat.eCommentStat     = CODECOMMENT_SLASHOUT;
        break;

    case '\n':
        msCodeStat.bEffeCodeFlag    = false;
        break;

    default:
        break;
    }
}



/**
 *  @fn     CFileCodeStatistics::fcsFsmSlashOutProc(char cChr)
 *  @brief  代码统计 块注释退出处理
 *
 *          块注释内, 检测到'*', 等待'/'结束块注释
 *  @param  [in] cChr   解码字符
 *  @return 无
 */
void CFileCodeStatistics::fcsFsmSlashOutProc(char cChr)
{
    switch ( cChr ) {
    case '/':
        msCodeStat.eCommentStat         = CODECOMMENT_IDLE;
        msCodeStat.bCommentCodeFlag     = false;
        msCodeStat.bCommentBlockOutFlag = true;
        break;

    case '*':
        break;

    case '\n':
        msCodeStat.bEffeCodeFlag    = false;
        break;

    default:
        msCodeStat.eCommentStat = CODECOMMENT_BOLCKIN;
        break;
    }
}


/**********************************************************************************************************
  END FILE
**********************************************************************************************************/