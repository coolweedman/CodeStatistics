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
class QMutex;

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
    void codeStatProgressSig(uint32_t ulCur, uint32_t ulTotal);         /**< 目录代码递归统计 处理过程信号 */
    void codeStatDoneSig(bool bStat = true);                            /**< 目录代码递归统计 处理完成信号 */

public slots:
    void codeStatOneFileStart(int iId);                                 /**< 目录代码递归统计 启动线程扫描一个文件 */
    void codeStatOneFileDoneProc(int iId, QString strFileNmae, const SCodeStatResultStru *psCodeStatResult);    /**< 目录代码递归统计 扫描完成处理 */

public:
    void codeStatFileGet(QString strDir);                               /**< 目录代码递归统计 根据目录读取文件 */
    void codeStatProc(QString strDir);                                  /**< 目录代码递归统计 统计 */
    void codeStatResGet(SCodeStatResultStru &sResStru);                 /**< 目录代码递归统计 结果获取 */
    void codeStatFilterSet(QStringList &rListStrFilter);                /**< 目录代码递归统计 读取过滤器 */
    void codeStatDetailResGet(QVector< QPair<QString, SCodeStatResultStru> > &rVecPair);    /**< 目录代码递归统计 详细结果获取 */

    void codeStatThreadCreate(void);                                    /**< 目录代码递归统计 创建线程 */
    void codeStatThreadStop(void);                                      /**< 目录代码递归统计 关闭线程 */

    static void codeStatResPrint(SCodeStatResultStru &sResStru);        /**< 目录代码递归统计 结果打印 */
    static void codeStatDetailResPrint(QVector< QPair<QString, SCodeStatResultStru> > &rVecPair);   /**< 目录代码递归统计 详细结果打印 */

private:
    QVector< QPair<QString, SCodeStatResultStru> > *mvecPairCodeStatResult; /**< 详细结果 */
    QVector<CFileCodeStatThread *>                 *mpFileCodeStatHandler;  /**< 线程句柄 */

    QStringList        *mpStrListFilter;    /**< 文件后缀过滤器 */
    QVector<QString>   *mpListFileFullName; /**< 文件全名, 包含路径 */
    QVector<QString>   *mpListFileName;     /**< 文件名, 不包含路径 */

    bool                mbFinishFlag;       /**< 扫描完成标志 */
    uint32_t            mulDoneCnt;         /**< 扫描结果计数 */
};

#endif // CODESTATISTICS


/**********************************************************************************************************
  END FILE
**********************************************************************************************************/
