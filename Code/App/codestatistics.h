#ifndef CODESTATISTICS
#define CODESTATISTICS

#include "filecodestatistics.h"
#include "dirscanstatistics.h"



/**********************************************************************************************************
  类型定义
**********************************************************************************************************/

class CCodeStatistics : public QObject {
    Q_OBJECT

public:
    CCodeStatistics(void);
   ~CCodeStatistics(void);

public:
    void codeStatProc(QString strDir);

private:
    QVector< QPair<QString, SCodeStatResultStru> > *mvecPairCodeStatResult;
};

#endif // CODESTATISTICS


/**********************************************************************************************************
  END FILE
**********************************************************************************************************/
