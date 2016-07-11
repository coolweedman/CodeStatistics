/******************************************************************************************************//**
 *  @file       dirscanstatistics.cpp
 *  @brief      目录扫描 源文件
 *
 *              递归扫描自定目录, 过滤后缀名, 获取文件名
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

#include "dirscanstatistics.h"
#include <QDir>
#include <QDebug>
#include <QFileInfo>


/**
 *  @fn     CDirScanStatistics::CDirScanStatistics(void)
 *  @brief  文件目录扫描过滤 构造函数
 *  @return 无
 */
CDirScanStatistics::CDirScanStatistics(void)
{
    mpvecStrFileName = new QVector<QString>();
    mpvecStrDirName  = new QVector<QString>();
    mpListFileFilter = new QStringList();

    mpListFileFilter->push_back( "*.c" );
    mpListFileFilter->push_back( "*.h" );
    mpListFileFilter->push_back( "*.cpp" );
}



/**
 *  @fn     CDirScanStatistics::~CDirScanStatistics(void)
 *  @brief  文件目录扫描过滤 析构函数
 *  @return 无
 */
CDirScanStatistics::~CDirScanStatistics(void)
{
    delete mpvecStrFileName;
    delete mpvecStrDirName;
    delete mpListFileFilter;
}



/**
 *  @fn     CDirScanStatistics::dirFileFilterScan(QString strPath)
 *  @brief  文件目录扫描过滤 目录扫描
 *  @param  [in] strPath    目录
 *  @return 无
 */
void CDirScanStatistics::dirFileFilterScan(QString strPath)
{
    QDir dir(strPath);

    if ( !dir.exists() ) {
        return;
    }

    QFileInfoList listDirInfo  = dir.entryInfoList( QDir::Dirs | QDir::NoDotAndDotDot );

    for ( int i=0; i<listDirInfo.length(); i++ ) {
        dirFileFilterScan( listDirInfo.at(i).filePath() );
    }

    QFileInfoList listFileInfo = dir.entryInfoList( *mpListFileFilter );

    for ( int i=0; i<listFileInfo.length(); i++ ) {
        mpvecStrDirName->push_back( strPath );
        mpvecStrFileName->push_back( listFileInfo.at(i).fileName() );
    }
}



/**
 *  @fn     CDirScanStatistics::dirFileScanedGet(QVector<QString> &rVecStrFileName)
 *  @brief  文件目录扫描过滤 结果获取
 *  @param  [out] rVecStrFileName   文件名
 *  @return 无
 */
void CDirScanStatistics::dirFileScanedGet(QVector<QString> &rVecStrFileName)
{
    for ( int i=0; i<mpvecStrFileName->length(); i++ ) {
        rVecStrFileName.push_back( mpvecStrDirName->at(i) + "/" + mpvecStrFileName->at(i) );
    }
}


void CDirScanStatistics::dirFileNameGet(QVector<QString> &rVecStrFileName)
{
    for ( int i=0; i<mpvecStrFileName->length(); i++ ) {
        rVecStrFileName.push_back( mpvecStrFileName->at(i) );
    }
}


/**
 *  @fn     CDirScanStatistics::dirPrint(void)
 *  @brief  文件目录扫描过滤 打印文件名
 *  @return 无
 */
void CDirScanStatistics::dirPrint(void)
{
    for ( int i=0; i<mpvecStrFileName->length(); i++ ) {
        qDebug()<<mpvecStrFileName->at(i);
    }
}



/**********************************************************************************************************
  END FILE
**********************************************************************************************************/
