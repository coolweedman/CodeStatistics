#include "filecodestatthread.h"
#include "filecodestatistics.h"
#include <QStringList>
#include <QDebug>
#include <QCoreApplication>
#include <QMutexLocker>


CFileCodeStatThread::CFileCodeStatThread(int iId)
{
    miThreadId  = iId;
    bFinishFlag = true;

    mphFileCodeStat = new CFileCodeStatistics();
}

CFileCodeStatThread::~CFileCodeStatThread(void)
{
    delete mphFileCodeStat;
}

void CFileCodeStatThread::fileCodeStatFileNameSet(QString strFullFileName)
{
    QMutexLocker lock(&mMutex);

    bFinishFlag      = false;
    mstrFullFileName = strFullFileName;

    QStringList strList = strFullFileName.split( "/" );
    mstrFileName = strList.at( strList.length()-1 );
}

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
