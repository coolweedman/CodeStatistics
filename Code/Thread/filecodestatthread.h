#ifndef FILECODESTATTHREAD
#define FILECODESTATTHREAD

#include <QObject>
#include <QThread>
#include "filecodestatistics.h"


class CFileCodeStatistics;


class CFileCodeStatThread : public QThread {
    Q_OBJECT

public:
    CFileCodeStatThread(int iId);
   ~CFileCodeStatThread(void);

public:
    void fileCodeStatFileNameSet(QString strFullFileName);

signals:
    void fileCodeDoneSig(int iId, QString strFileNmae, const SCodeStatResultStru *psCodeStatResult);

protected:
    void run(void);

private:
    int                     miThreadId;
    CFileCodeStatistics    *mphFileCodeStat;
    QString                 mstrFullFileName;
    QString                 mstrFileName;
    SCodeStatResultStru     msCodeStatResult;
};

#endif // FILECODESTATTHREAD

