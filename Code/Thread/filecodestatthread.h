/******************************************************************************************************//**
 *  @file       filecodestatthread.h
 *  @brief      文件代码扫描线程 头文件
 *
 *              启动多线程扫描文件 统计代码
 *  @author     coolweedman
 *  @version    V1.00
 *  @date       2016-7-18
 *********************************************************************************************************/

#ifndef FILECODESTATTHREAD
#define FILECODESTATTHREAD

#include <QObject>
#include <QThread>
#include "filecodestatistics.h"
#include <QMutex>

/**********************************************************************************************************
  类型声明
**********************************************************************************************************/

class CFileCodeStatistics;



/**********************************************************************************************************
  类型定义
**********************************************************************************************************/

/**
 *  @class  CFileCodeStatThread
 *  @brief  文件代码扫描线程 类
 */
class CFileCodeStatThread : public QThread {
    Q_OBJECT

public:
    CFileCodeStatThread(int iId);   /**< 文件代码扫描线程 构造函数 */
   ~CFileCodeStatThread(void);      /**< 文件代码扫描线程 析构函数 */

public:
    void fileCodeStatFileNameSet(QString strFullFileName);  /**< 文件代码扫描线程 设置文件名 */

signals:
    void fileCodeDoneSig(int iId, QString strFileNmae, const SCodeStatResultStru *psCodeStatResult);    /**< 文件代码扫描线程 扫描结果信号 */

protected:
    void run(void);         /**< 多线程运行函数 */

public:
    bool                    bFinishFlag;        /**< 完成状态 */

private:
    int                     miThreadId;         /**< 线程ID */
    CFileCodeStatistics    *mphFileCodeStat;    /**< 线程状态 */
    QString                 mstrFullFileName;   /**< 文件全名 */
    QString                 mstrFileName;       /**< 文件名 */
    SCodeStatResultStru     msCodeStatResult;   /**< 扫描结果 */

    QMutex                  mMutex;             /**< 互斥信号量 */
};

#endif // FILECODESTATTHREAD

/**********************************************************************************************************
  END FILE
**********************************************************************************************************/
