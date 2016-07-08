#include "codestatistics.h"
#include <QVector>
#include <QString>
#include <QPair>
#include <QDebug>


CCodeStatistics::CCodeStatistics(void)
{
    mvecPairCodeStatResult = new QVector< QPair<QString, SCodeStatResultStru> >();
}

CCodeStatistics::~CCodeStatistics(void)
{

}


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

    for ( int i=0; i<mvecPairCodeStatResult->length(); i++ ) {
        qDebug()<<mvecPairCodeStatResult->at(i).first;
        CFileCodeStatistics::fcsResPrint( mvecPairCodeStatResult->at(i).second );
        qDebug()<<endl;
    }
}

/**********************************************************************************************************
  END FILE
**********************************************************************************************************/
