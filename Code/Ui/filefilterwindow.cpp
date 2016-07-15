/******************************************************************************************************//**
 *  @file       filefilterwindow.cpp
 *  @brief      后缀名过滤 源文件
 *
 *              后缀名过滤
 *              配置后缀名 保存配置 恢复配置 自定义后缀名
 *  @author     coolweedman
 *  @version    V1.00
 *  @date       2016-7-13
 *********************************************************************************************************/

#include "filefilterwindow.h"
#include "ui_filefilterwindow.h"
#include <QSettings>
#include <QDebug>


/**********************************************************************************************************
  宏定义
**********************************************************************************************************/

#define FFW_CFG_FILE_NAME           ( "Cfg/FileFilter.ini" )

#define FFW_CFG_FILE_C              ( "C" )
#define FFW_CFG_FILE_H              ( "H" )
#define FFW_CFG_FILE_CPP            ( "CPP" )
#define FFW_CFG_FILE_JAVA           ( "JAVA" )
#define FFW_CFG_FILE_CS             ( "CS" )
#define FFW_CFG_FILE_TXT            ( "TXT" )
#define FFW_CFG_FILE_OTHER          ( "OHTER" )
#define FFW_CFG_FILE_TEXT           ( "TEXT" )



/**
 *  @fn     FileFilterWindow::FileFilterWindow(QWidget *parent)
 *  @brief  文件过滤配置 构造函数
 *  @param  [in] parent 父窗口
 *  @return 无
 */
FileFilterWindow::FileFilterWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FileFilterWindow)
{
    ui->setupUi(this);

    mpVecStrFileFilter = new QVector<QString>();

    ffwReStore();
}



/**
 *  @fn     FileFilterWindow::~FileFilterWindow()
 *  @brief  文件过滤配置 析构函数
 *  @return 无
 */
FileFilterWindow::~FileFilterWindow()
{
    ffwSave();

    delete mpVecStrFileFilter;
    delete ui;
}



/**
 *  @fn     FileFilterWindow::ffwSave(void)
 *  @brief  文件过滤配置 保存配置
 *  @return 无
 */
void FileFilterWindow::ffwSave(void)
{
    ffwUi2Stru();
    ffwStru2Setting();
}



/**
 *  @fn     FileFilterWindow::ffwReStore(void)
 *  @brief  文件过滤配置 恢复配置
 *  @return 无
 */
void FileFilterWindow::ffwReStore(void)
{
    ffwSetting2Stru();
    ffwStru2Ui();
    ffwStru2String();
}



/**
 *  @fn     FileFilterWindow::ffwUi2Stru(void)
 *  @brief  文件过滤配置 UI转结构体
 *  @return 无
 */
void FileFilterWindow::ffwUi2Stru(void)
{
    msFileFilterStru.bC     = ui->checkBoxC->isChecked();
    msFileFilterStru.bH     = ui->checkBoxH->isChecked();
    msFileFilterStru.bCpp   = ui->checkBoxCpp->isChecked();
    msFileFilterStru.bJava  = ui->checkBoxJava->isChecked();
    msFileFilterStru.bCs    = ui->checkBoxCs->isChecked();
    msFileFilterStru.bTxt   = ui->checkBoxTxt->isChecked();
    msFileFilterStru.bOther = ui->checkBoxOther->isChecked();

    msFileFilterStru.strOtherText = ui->textEditFilterText->toPlainText();
}



/**
 *  @fn     FileFilterWindow::ffwStru2Ui(void)
 *  @brief  文件过滤配置 结构体转UI
 *  @return 无
 */
void FileFilterWindow::ffwStru2Ui(void)
{
    ui->checkBoxC->setChecked(       msFileFilterStru.bC );
    ui->checkBoxH->setChecked(       msFileFilterStru.bH );
    ui->checkBoxCpp->setChecked(     msFileFilterStru.bCpp );
    ui->checkBoxJava->setChecked(    msFileFilterStru.bJava );
    ui->checkBoxCs->setChecked(      msFileFilterStru.bCs );
    ui->checkBoxTxt->setChecked(     msFileFilterStru.bTxt );
    ui->checkBoxOther->setChecked(   msFileFilterStru.bOther );

    ui->textEditFilterText->setEnabled( msFileFilterStru.bOther );
    ui->textEditFilterText->setText( msFileFilterStru.strOtherText );
}



/**
 *  @fn     FileFilterWindow::ffwSetting2Stru(void)
 *  @brief  文件过滤配置 配置转结构体
 *  @return 无
 */
void FileFilterWindow::ffwSetting2Stru(void)
{
    QSettings *pSetting = new QSettings( FFW_CFG_FILE_NAME, QSettings::IniFormat );

    msFileFilterStru.bC     = pSetting->value(FFW_CFG_FILE_C,     true).toBool();
    msFileFilterStru.bH     = pSetting->value(FFW_CFG_FILE_H,     true).toBool();
    msFileFilterStru.bCpp   = pSetting->value(FFW_CFG_FILE_CPP,   true).toBool();
    msFileFilterStru.bJava  = pSetting->value(FFW_CFG_FILE_JAVA,  false).toBool();
    msFileFilterStru.bCs    = pSetting->value(FFW_CFG_FILE_CS,    false).toBool();
    msFileFilterStru.bTxt   = pSetting->value(FFW_CFG_FILE_TXT,   false).toBool();
    msFileFilterStru.bOther = pSetting->value(FFW_CFG_FILE_OTHER, false).toBool();

    msFileFilterStru.strOtherText = pSetting->value(FFW_CFG_FILE_TEXT,  "").toString();

    delete pSetting;
}



/**
 *  @fn     FileFilterWindow::ffwStru2Setting(void)
 *  @brief  文件过滤配置 结构体转配置
 *  @return 无
 */
void FileFilterWindow::ffwStru2Setting(void)
{
    QSettings *pSetting = new QSettings( FFW_CFG_FILE_NAME, QSettings::IniFormat );

    pSetting->setValue( FFW_CFG_FILE_C,     msFileFilterStru.bC );
    pSetting->setValue( FFW_CFG_FILE_H,     msFileFilterStru.bH );
    pSetting->setValue( FFW_CFG_FILE_CPP,   msFileFilterStru.bCpp );
    pSetting->setValue( FFW_CFG_FILE_JAVA,  msFileFilterStru.bJava );
    pSetting->setValue( FFW_CFG_FILE_CS,    msFileFilterStru.bCs );
    pSetting->setValue( FFW_CFG_FILE_TXT,   msFileFilterStru.bTxt );
    pSetting->setValue( FFW_CFG_FILE_OTHER, msFileFilterStru.bOther );
    pSetting->setValue( FFW_CFG_FILE_TEXT,  msFileFilterStru.strOtherText );

    delete pSetting;
}



/**
 *  @fn     FileFilterWindow::ffwStru2String(void)
 *  @brief  文件过滤配置 结构体转过滤字符串
 *  @return 无
 */
void FileFilterWindow::ffwStru2String(void)
{
    mpVecStrFileFilter->clear();

    if ( msFileFilterStru.bC ) {
        mpVecStrFileFilter->push_back( "*.c" );
    }
    if ( msFileFilterStru.bH ) {
        mpVecStrFileFilter->push_back( "*.h" );
    }
    if ( msFileFilterStru.bCpp ) {
        mpVecStrFileFilter->push_back( "*.cpp" );
    }
    if ( msFileFilterStru.bJava ) {
        mpVecStrFileFilter->push_back( "*.java" );
    }
    if ( msFileFilterStru.bCs ) {
        mpVecStrFileFilter->push_back( "*.cs" );
    }
    if ( msFileFilterStru.bTxt ) {
        mpVecStrFileFilter->push_back( "*.txt" );
    }

    if ( msFileFilterStru.bOther ) {
        mpVecStrFileFilter->clear();
        QStringList strList = msFileFilterStru.strOtherText.split( "\n" );

        for ( int i=0; i<strList.length(); i++ ) {
            mpVecStrFileFilter->push_back( strList.at(i) );
            qDebug()<<mpVecStrFileFilter->at(i);
        }
    }
}



/**
 *  @fn     FileFilterWindow::ffwFilterGet(QStringList &rFilter)
 *  @brief  文件过滤配置 获取过滤字符串
 *  @param  [out] rFilter   过滤字符串
 *  @return 无
 */
void FileFilterWindow::ffwFilterGet(QStringList &rFilter)
{
    rFilter.clear();

    for ( int i=0; i<mpVecStrFileFilter->length(); i++ ) {
        rFilter.push_back( mpVecStrFileFilter->at(i) );
    }
}


void FileFilterWindow::on_checkBoxOther_toggled(bool checked)
{
    ui->textEditFilterText->setEnabled( checked );
}


void FileFilterWindow::on_pushButtonOk_clicked()
{
    ffwUi2Stru();
    ffwStru2String();

    emit ffwFilterSig( *mpVecStrFileFilter );

    this->close();
}


void FileFilterWindow::on_pushButtonCancel_clicked()
{
    this->close();
}



/**********************************************************************************************************
  END FILE
**********************************************************************************************************/
