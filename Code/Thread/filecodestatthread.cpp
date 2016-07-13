#include "filecodestatthread.h"
#include "filecodestatistics.h"
#include <QStringList>
#include <QDebug>


CFileCodeStatThread::CFileCodeStatThread(int iId)
{
    miThreadId = iId;

    mphFileCodeStat = new CFileCodeStatistics();
}

CFileCodeStatThread::~CFileCodeStatThread(void)
{

}

void CFileCodeStatThread::fileCodeStatFileNameSet(QString strFullFileName)
{
    mstrFullFileName = strFullFileName;

    QStringList strList = strFullFileName.split( "/" );
    mstrFileName = strList.at( strList.length()-1 );
}

void CFileCodeStatThread::run(void)
{
    qDebug()<<"run "<<miThreadId;

    mphFileCodeStat->fcsFileScan( mstrFullFileName );
    mphFileCodeStat->fcsResGet( msCodeStatResult );

    emit fileCodeDoneSig( miThreadId, mstrFileName, &msCodeStatResult );

    qDebug()<<"end run "<<miThreadId;
}
