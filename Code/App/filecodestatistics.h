/******************************************************************************************************//**
 *  @file       filecodestatistics.h
 *  @brief      代码统计 头文件
 *
 *              根据文件名, 统计代码
 *              有效代码行/注释行/空行/总行数
 *  @author     coolweedman
 *  @version    V1.00
 *  @date       2016-7-8
 *********************************************************************************************************/

#ifndef FILECODESTATISTICS
#define FILECODESTATISTICS

#include <QObject>
#include "typedefs.h"


/**********************************************************************************************************
  类型声明
**********************************************************************************************************/

class QFile;



/**********************************************************************************************************
  类型定义
**********************************************************************************************************/

/**
 *  @enum   ECodeCommentStat
 *  @brief  代码统计 状态
 */
enum ECodeCommentStat {
    CODECOMMENT_IDLE = 0,   /**< 未确定状态 */
    CODECOMMENT_SLASHIN,    /**< '/', 准备进入注释状态 */
    CODECOMMENT_LINEIN,     /**< 行注释状态 */
    CODECOMMENT_BOLCKIN,    /**< 块注释状态 */
    CODECOMMENT_SLASHOUT,   /**< 退出块注释 */
};

/**
 *  @struct SCodeStatisticsStru
 *  @brief  代码统计 过程结构体
 */
struct SCodeStatisticsStru {
    ECodeCommentStat    eCommentStat;           /**< 代码扫描状态 */

    bool                bEffeCodeFlag;          /**< 有效代码标识 */
    bool                bCommentCodeFlag;       /**< 注释代码标识 */
    bool                bEmptyLineFlag;         /**< 空行标识 */

    bool                bCommentBlockOutFlag;   /**< 块注释退出标识 */

    uint32_t            uiEffeCodeLines;        /**< 有效代码行数 */
    uint32_t            uiCommentCodeLines;     /**< 注释代码行数 */
    uint32_t            uiEmptyLineNum;         /**< 空行代码行数 */
    uint32_t            uiTotalLineNum;         /**< 总行数 */
};

/**
 *  @struct SCodeStatisticsStru
 *  @brief  代码统计 结果结构体
 */
struct SCodeStatResultStru {
    uint32_t            uiEffeCodeLines;        /**< 有效代码行数 */
    uint32_t            uiCommentCodeLines;     /**< 注释代码行数 */
    uint32_t            uiEmptyLineNum;         /**< 空行代码行数 */
    uint32_t            uiTotalLineNum;         /**< 总行数 */
};
Q_DECLARE_METATYPE(SCodeStatResultStru)

/**
 *  @class  CFileCodeStatistics
 *  @brief  代码统计 类
 */
class CFileCodeStatistics : public QObject {
public:
    CFileCodeStatistics(void);                      /**< 代码统计 构造函数 */
   ~CFileCodeStatistics(void);                      /**< 代码统计 析构函数 */

public:
    void fcsFileScan(QString strFileName);          /**< 代码统计 文件扫描 */
    void fcsResGet(SCodeStatResultStru &sStru);     /**< 代码统计 结果获取 */

    static void fcsResPrint(const SCodeStatResultStru &sStru);   /**< 代码统计 结果打印 */

protected:
    void fcsStruInit(void);                         /**< 代码统计 结构体初始化 */
    void fcsFsmCharProc(char cChr);                 /**< 代码统计 字符解码状态机 */
    void fcsLineInc(void);                          /**< 代码统计 累计行数 */

    void fcsFsmIdelProc(char cChr);                 /**< 代码统计 未确定状态才处理 */
    void fcsFsmSlashInProc(char cChr);              /**< 代码统计 '/'状态处理 */
    void fcsFsmLineInProc(char cChr);               /**< 代码统计 行注释处理 */
    void fcsFsmBlockInProc(char cChr);              /**< 代码统计 块注释处理 */
    void fcsFsmSlashOutProc(char cChr);             /**< 代码统计 块注释退出处理 */

protected:
    SCodeStatisticsStru     msCodeStat;             /**< 代码统计 统计结构体 */
};

#endif // FILECODESTATISTICS


/**********************************************************************************************************
  END FILE
**********************************************************************************************************/
