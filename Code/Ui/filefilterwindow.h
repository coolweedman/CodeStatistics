/******************************************************************************************************//**
 *  @file       filefilterwindow.h
 *  @brief      后缀名过滤 头文件
 *
 *              后缀名过滤
 *              配置后缀名 保存配置 恢复配置 自定义后缀名
 *  @author     coolweedman
 *  @version    V1.00
 *  @date       2016-7-13
 *********************************************************************************************************/

#ifndef FILEFILTERWINDOW_H
#define FILEFILTERWINDOW_H

#include <QMainWindow>

namespace Ui {
class FileFilterWindow;
}

/**********************************************************************************************************
  类型定义
**********************************************************************************************************/

/**
 *  @struct SFileFilterStru
 *  @brief  文件过滤 结构体
 */
struct SFileFilterStru {
    bool bC;        /**< c文件 */
    bool bH;        /**< h文件 */
    bool bCpp;      /**< cpp文件 */
    bool bJava;     /**< java文件 */
    bool bCs;       /**< cs文件 */
    bool bTxt;      /**< txt文件 */
    bool bOther;    /**< 其它文件 */

    QString strOtherText;   /**< 自定义文件后缀字符串 */
};

/**
 *  @class  FileFilterWindow
 *  @brief  文件过滤配置 类
 */
class FileFilterWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit FileFilterWindow(QWidget *parent = 0); /**< 文件过滤配置 构造函数 */
    ~FileFilterWindow();                            /**< 文件过滤配置 析构函数 */

signals:
    void ffwFilterSig(QVector<QString> &rVecStrFilter); /**< 文件过滤配置 文件过滤信号 */

protected:
    void ffwSave(void);         /**< 文件过滤配置 保存配置 */
    void ffwReStore(void);      /**< 文件过滤配置 恢复配置 */

    void ffwUi2Stru(void);      /**< 文件过滤配置 UI转结构体 */
    void ffwStru2Ui(void);      /**< 文件过滤配置 结构体转UI */

    void ffwSetting2Stru(void); /**< 文件过滤配置 配置转结构体 */
    void ffwStru2Setting(void); /**< 文件过滤配置 结构体转配置 */

    void ffwStru2String(void);  /**< 文件过滤配置 结构体转过滤字符串 */

public:
    void ffwFilterGet(QStringList &rFilter);    /**< 文件过滤配置 获取过滤字符串 */

private slots:
    void on_checkBoxOther_toggled(bool checked);
    void on_pushButtonOk_clicked();
    void on_pushButtonCancel_clicked();

private:
    Ui::FileFilterWindow   *ui;
    QVector<QString>       *mpVecStrFileFilter; /**< 文件过滤配置 过滤字符串 */
    SFileFilterStru         msFileFilterStru;   /**< 文件过滤配置 过滤结构体 */
};

#endif // FILEFILTERWINDOW_H

/**********************************************************************************************************
  END FILE
**********************************************************************************************************/
