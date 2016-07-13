/******************************************************************************************************//**
 *  @file       dirscanstatistics.h
 *  @brief      目录扫描 源文件
 *
 *              递归扫描自定目录, 过滤后缀名, 获取文件名
 *  @author     CaiWeiMou
 *  @version    V1.00
 *  @date       2016-7-8
 *
 *  @note       Guangzhou ZLGMCU Technology Co., LTD
 *
 *  @par
 *      广州周立功单片机科技有限公司所提供的所有服务内容旨在协助客户加速产品的研发进度，在服务过程中所提供
 *  的任何程序、文档、测试结果、方案、支持等资料和信息，都仅供参考，客户有权不使用或自行参考修改，本公司不
 *  提供任何的完整性、可靠性等保证，若在客户使用过程中因任何原因造成的特别的、偶然的或间接的损失，本公司不
 *  承担任何责任。
 *                                                                        ——广州周立功单片机科技有限公司
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
