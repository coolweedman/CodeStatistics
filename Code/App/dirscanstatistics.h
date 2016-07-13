/******************************************************************************************************//**
 *  @file       dirscanstatistics.h
 *  @brief      目录扫描 源文件
 *
 *              递归扫描自定目录, 过滤后缀名, 获取文件名
 *  @author     coolweedman
 *  @version    V1.00
 *  @date       2016-7-8
 *********************************************************************************************************/

#ifndef DIRSCANSTATISTICS
#define DIRSCANSTATISTICS

#include "typedefs.h"
#include <QObject>


/**********************************************************************************************************
  类型声明
**********************************************************************************************************/

class QDir;


/**********************************************************************************************************
  类型定义
**********************************************************************************************************/

/**
 *  @class  CDirScanStatistics
 *  @brief  文件目录扫描过滤 类
 */
class CDirScanStatistics : public QObject {

    Q_OBJECT
public:
    CDirScanStatistics(void);   /**< 文件目录扫描过滤 构造函数 */
   ~CDirScanStatistics(void);   /**< 文件目录扫描过滤 析构函数 */

public:
    void dirFileFilterSet(const QStringList &rFilter);
    void dirFileFilterGet(QStringList &rFilter);
    void dirFileFilterScan(QString strPath);                        /**< 文件目录扫描过滤 目录扫描 */
    void dirFileScanedGet(QVector<QString> &rVecStrFileName);       /**< 文件目录扫描过滤 结果获取 */
    void dirFileNameGet(QVector<QString> &rVecStrFileName);         /**< 文件目录扫描过滤 结果获取 */
    void dirPrint(void);                                            /**< 文件目录扫描过滤 打印文件名 */

private:
    QVector<QString>   *mpvecStrDirName;        /**< 文件夹 */
    QVector<QString>   *mpvecStrFileName;       /**< 文件名 */
    QStringList        *mpListFileFilter;       /**< 过滤规则 */
};



#endif // DIRSCANSTATISTICS

/**********************************************************************************************************
  END FILE
**********************************************************************************************************/
