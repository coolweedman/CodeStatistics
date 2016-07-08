#include "filecodestatistics.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>


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

CFileCodeStatistics::~CFileCodeStatistics(void)
{
    if ( NULL != mpFile ) {
        mpFile->close();
        delete mpFile;
    }
}

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


void CFileCodeStatistics::fcsEcho(void)
{
    QTextStream textStream( mpFile );

    while ( !textStream.atEnd() ) {
        qDebug()<<textStream.readLine();
    }
}


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

void CFileCodeStatistics::fcsResultPrint(void)
{
    qDebug()<<"EffeCode Line "<<msCodeStat.uiEffeCodeLines;
    qDebug()<<"Comment  Line "<<msCodeStat.uiCommentCodeLines;
    qDebug()<<"Empty    Line "<<msCodeStat.uiEmptyLineNum;
    qDebug()<<"Total    Line "<<msCodeStat.uiTotalLineNum;
}

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

//检测到'/'后, 等待'/'行注释 '*'块注释
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

//行注释
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

//块注释内, 等待'*'
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

//块注释内, 检测到'*', 等待'/'结束块注释
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
