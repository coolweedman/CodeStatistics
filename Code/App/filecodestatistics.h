#ifndef FILECODESTATISTICS
#define FILECODESTATISTICS

#include <QObject>
#include "typedefs.h"

class QFile;

enum ECodeCommentStat {
    CODECOMMENT_IDLE = 0,
    CODECOMMENT_SLASHIN,
    CODECOMMENT_LINEIN,
    CODECOMMENT_BOLCKIN,
    CODECOMMENT_SLASHOUT,
};


struct SEcodeStatisticsStru {
    ECodeCommentStat    eCommentStat;

    bool                bEffeCodeFlag;
    bool                bCommentCodeFlag;
    bool                bEmptyLineFlag;

    bool                bCommentBlockOutFlag;

    uint32_t            uiEffeCodeLines;
    uint32_t            uiCommentCodeLines;
    uint32_t            uiEmptyLineNum;
    uint32_t            uiTotalLineNum;
};

class CFileCodeStatistics : QObject {
public:
    CFileCodeStatistics(QString strFileName);
   ~CFileCodeStatistics(void);

public:
    void fcsStruInit(void);
    void fcsFsmCharProc(char cChr);
    void fcsFileScan(void);
    void fcsLineInc(void);
    void fcsResultPrint(void);

    void fcsFsmIdelProc(char cChr);
    void fcsFsmSlashInProc(char cChr);
    void fcsFsmLineInProc(char cChr);
    void fcsFsmBlockInProc(char cChr);
    void fcsFsmSlashOutProc(char cChr);

    void fcsEcho(void);

protected:
    QFile                  *mpFile;
    SEcodeStatisticsStru    msCodeStat;
};

#endif // FILECODESTATISTICS

