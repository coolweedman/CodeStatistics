#ifndef CODESTATISTICSWINDOW_H
#define CODESTATISTICSWINDOW_H

#include <QMainWindow>
#include "codestatistics.h"

namespace Ui {
class CodeStatisticsWindow;
}

/**********************************************************************************************************
  类型声明
**********************************************************************************************************/

class QLabel;



/**********************************************************************************************************
  类型定义
**********************************************************************************************************/

/**
 *  @class  CodeStatisticsWindow
 *  @brief  代码统计窗口 类
 */
class CodeStatisticsWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit CodeStatisticsWindow(QWidget *parent = 0); /**< 代码统计窗口 构造函数 */
    ~CodeStatisticsWindow();                            /**< 代码统计窗口 析构函数 */

private:
    void statusBarInit(void);               /**< 代码统计窗口 状态栏初始化 */

private:
    void codeStatStatusBarUpdate(void);     /**< 代码统计窗口 状态栏更新 */
    void codeStatTableWidgetUpdate(void);   /**< 代码统计窗口 详细信息更新 */

private slots:
    void on_pushButtonLookFor_clicked();
    void on_pushButtonOk_clicked();
    void on_actionExit_triggered();

    void on_actionAbout_triggered();

private:
    Ui::CodeStatisticsWindow   *ui;
    SCodeStatResultStru         msCodeStatResult;   /**< 代码统计窗口 统计结果 */

    QVector<QPair<QString, SCodeStatResultStru> > msVecCodeStatDetailResult;    /**< 代码统计窗口 详细计算结果 */

    QLabel  *mpLabelEffeLine;
    QLabel  *mpLabelCommentLine;
    QLabel  *mpLabelEmptyLine;
    QLabel  *mpLabelTotalLine;
    QLabel  *mpLabelTotalFiles;
};

#endif // CODESTATISTICSWINDOW_H

/**********************************************************************************************************
  END FILE
**********************************************************************************************************/
