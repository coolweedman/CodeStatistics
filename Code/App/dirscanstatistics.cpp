/******************************************************************************************************//**
 *  @file       dirscanstatistics.cpp
 *  @brief      目录扫描 源文件
 *
 *              递归扫描自定目录, 过滤后缀名, 获取文件名
 *  @author     coolweedman
 *  @version    V1.00
 *  @date       2016-7-8
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


void CDirScanStatistics::dirFileFilterSet(const QStringList &rFilter)
{
    for ( int i=0; i<rFilter.length(); i++ ) {
        mpListFileFilter->push_back( rFilter.at(i) );
    }
}

void CDirScanStatistics::dirFileFilterGet(QStringList &rFilter)
{
    for ( int i=0; i<mpListFileFilter->length(); i++ ) {
        rFilter.push_back( mpListFileFilter->at(i) );
    }
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
