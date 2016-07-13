/******************************************************************************************************//**
 *  @file       codestatistics.h
 *  @brief      目录代码递归统计 头文件
 *
 *              递归扫描自定目录, 过滤后缀名, 获取文件名
 *              统计有效代码行数/注释行/空行/总行数
 *  @author     coolweedman
 *  @version    V1.00
 *  @date       2016-7-8
 *********************************************************************************************************/

#ifndef CODESTATISTICS
#define CODESTATISTICS

#include "filecodestatistics.h"
#include "dirscanstatistics.h"
#include <QThread>


class CFileCodeStatThread;

/**********************************************************************************************************
  类型定义
**********************************************************************************************************/

/**
 *  @class  CCodeStatistics
 *  @brief  目录代码递归统计 类
 */
class CCodeStatistics : public QObject {
    Q_OBJECT

public:
    CCodeStatistics(void);  /**< 目录代码递归统计 构造函数 */
   ~CCodeStatistics(void);  /**< 目录代码递归统计 析构函数 */

signals:
    void codeStatProgressSig(uint32_t ulCur, uint32_t ulTotal);
    void codeStatDoneSig(void);

public slots:
    void codeStatOneFileStart(int iId);
    void codeStatOneFileDoneProc(int iId, QString strFileNmae, const SCodeStatResultStru *psCodeStatResult);

public:
    void codeStatFileGet(QString strDir);
    void codeStatProc(QString strDir);                                  /**< 目录代码递归统计 统计 */
    void codeStatResGet(SCodeStatResultStru &sResStru);                 /**< 目录代码递归统计 结果获取 */
    void codeStatFilterSet(QStringList &rListStrFilter);
    void codeStatDetailResGet(QVector< QPair<QString, SCodeStatResultStru> > &rVecPair);    /**< 目录代码递归统计 详细结果获取 */

    static void codeStatResPrint(SCodeStatResultStru &sResStru);        /**< 目录代码递归统计 结果打印 */
    static void codeStatDetailResPrint(QVector< QPair<QString, SCodeStatResultStru> > &rVecPair);   /**< 目录代码递归统计 详细结果打印 */

private:
    QVector< QPair<QString, SCodeStatResultStru> > *mvecPairCodeStatResult; /**< 详细结果 */
    QVector<CFileCodeStatThread *>                 *mpFileCodeStatHandler;

    QStringList        *mpStrListFilter;
    QVector<QString>   *mpListFileFullName;
    QVector<QString>   *mpListFileName;
};

#endif // CODESTATISTICS


/**********************************************************************************************************
  END FILE
**********************************************************************************************************/
