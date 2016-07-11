/******************************************************************************************************//**
 *  @file       codestatistics.h
 *  @brief      目录代码递归统计 头文件
 *
 *              递归扫描自定目录, 过滤后缀名, 获取文件名
 *              统计有效代码行数/注释行/空行/总行数
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

#ifndef CODESTATISTICS
#define CODESTATISTICS

#include "filecodestatistics.h"
#include "dirscanstatistics.h"



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

public:
    void codeStatProc(QString strDir);                                  /**< 目录代码递归统计 统计 */
    void codeStatResGet(SCodeStatResultStru &sResStru);                 /**< 目录代码递归统计 结果获取 */
    void codeStatDetailResGet(QVector< QPair<QString, SCodeStatResultStru> > &rVecPair);    /**< 目录代码递归统计 详细结果获取 */

    static void codeStatResPrint(SCodeStatResultStru &sResStru);        /**< 目录代码递归统计 结果打印 */
    static void codeStatDetailResPrint(QVector< QPair<QString, SCodeStatResultStru> > &rVecPair);   /**< 目录代码递归统计 详细结果打印 */

private:
    QVector< QPair<QString, SCodeStatResultStru> > *mvecPairCodeStatResult; /**< 详细结果 */
};

#endif // CODESTATISTICS


/**********************************************************************************************************
  END FILE
**********************************************************************************************************/
