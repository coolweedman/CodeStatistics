/******************************************************************************************************//**
 *  @file       codestatisticswindow.cpp
 *  @brief      代码统计窗口 源文件
 *
 *              统计代码
 *              选择路径, 配置后缀名, 计算代码量, 显示结果
 *  @author     coolweedman
 *  @version    V1.00
 *  @date       2016-7-13
 *********************************************************************************************************/

#include "codestatisticswindow.h"
#include "ui_codestatisticswindow.h"
#include <QFileDialog>
#include <QLabel>
#include <QUrl>
#include <QDesktopServices>
#include <QProgressBar>
#include "filefilterwindow.h"
#include <QTime>
#include <QDebug>
#include <QMessageBox>
#include <QClipboard>
#include "applanguage.h"


/**********************************************************************************************************
  宏定义
**********************************************************************************************************/

#define CODE_STAT_VERSION           ( 104 )



/**
 *  @fn     CodeStatisticsWindow::CodeStatisticsWindow(QWidget *parent)
 *  @brief  代码统计窗口 构造函数
 *  @param  [in]    parent  父窗口
 *  @return 无
 */
CodeStatisticsWindow::CodeStatisticsWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CodeStatisticsWindow)
{
    ui->setupUi(this);

    statusBarInit();

    this->setWindowTitle( tr("Code Statistics V") + QString::number( CODE_STAT_VERSION/100.0, 'f', 2 ) );

    mphFileFilterWindow = new FileFilterWindow(this);
    mphCodeStat = new CCodeStatistics();

    connect( mphCodeStat,
             SIGNAL(codeStatProgressSig(uint32_t,uint32_t)),
             this,
             SLOT(codeStatProgressUpdate(uint32_t,uint32_t)) );
    connect( mphCodeStat,
             SIGNAL(codeStatDoneSig(bool)),
             this,
             SLOT(codeStatProgressDone(bool)) );
}



/**
 *  @fn     CodeStatisticsWindow::~CodeStatisticsWindow(QWidget *parent)
 *  @brief  代码统计窗口 析构函数
 *  @return 无
 */
CodeStatisticsWindow::~CodeStatisticsWindow()
{
    delete mphFileFilterWindow;
    delete mphCodeStat;
    delete ui;
}



/**
 *  @fn     CodeStatisticsWindow::statusBarInit(void)
 *  @brief  代码统计窗口 状态栏初始化
 *  @return 无
 */
void CodeStatisticsWindow::statusBarInit(void)
{
    mpLabelEffeLine    = new QLabel();
    mpLabelCommentLine = new QLabel();
    mpLabelEmptyLine   = new QLabel();
    mpLabelTotalLine   = new QLabel();
    mpLabelTotalFiles  = new QLabel();
    mpLabelTotalTime   = new QLabel();

    mpLabelEffeLine->setText( tr("Effe: ?") );
    mpLabelCommentLine->setText( tr("Comment: ?") );
    mpLabelEmptyLine->setText( tr("Empty: ?") );
    mpLabelTotalLine->setText( tr("Total: ?") );
    mpLabelTotalFiles->setText( tr("File(s): ?") );
    mpLabelTotalTime->setText( tr("Time(s): ?") );

    statusBar()->addWidget( mpLabelEffeLine );
    statusBar()->addWidget( mpLabelCommentLine );
    statusBar()->addWidget( mpLabelEmptyLine );
    statusBar()->addWidget( mpLabelTotalLine );
    statusBar()->addWidget( mpLabelTotalFiles );
    statusBar()->addWidget( mpLabelTotalTime );

    mpProgressBar = new QProgressBar();
    mpProgressBar->setFixedHeight( 20 );
    statusBar()->addWidget( mpProgressBar );
    mpProgressBar->setVisible( false );
}



/**
 *  @fn     CodeStatisticsWindow::codeStatStatusBarUpdate(void)
 *  @brief  代码统计窗口 状态栏更新
 *  @return 无
 */
void CodeStatisticsWindow::codeStatStatusBarUpdate(void)
{
    mpLabelEffeLine->setText( tr(" Effe: ") + QString::number(msCodeStatResult.uiEffeCodeLines) );
    mpLabelCommentLine->setText( tr(" Comment: ") + QString::number(msCodeStatResult.uiCommentCodeLines) );
    mpLabelEmptyLine->setText( tr(" Empty: ") + QString::number(msCodeStatResult.uiEmptyLineNum) );
    mpLabelTotalLine->setText( tr(" Total: ") + QString::number(msCodeStatResult.uiTotalLineNum) );
    mpLabelTotalFiles->setText( tr(" File(s): ") + QString::number(msVecCodeStatDetailResult.length()) );
}



/**
 *  @fn     CodeStatisticsWindow::codeStatTableWidgetUpdate(void)
 *  @brief  代码统计窗口 详细信息更新
 *  @return 无
 */
void CodeStatisticsWindow::codeStatTableWidgetUpdate(void)
{
    ui->tableWidget->clear();
    ui->tableWidget->setSortingEnabled( true );

    QStringList strTitle;

    strTitle<<tr("File");
    strTitle<<tr("Valid Code Line(s)");
    strTitle<<tr("Comment Line(s)");
    strTitle<<tr("Empty Line(s)");
    strTitle<<tr("Total Line(s)");
    ui->tableWidget->setHorizontalHeaderLabels( strTitle );

    ui->tableWidget->setRowCount( msVecCodeStatDetailResult.length() );

    for ( int i=0; i<msVecCodeStatDetailResult.length(); i++ ) {
        QVector<QTableWidgetItem *> vecItem;

        for ( int j=0; j<ui->tableWidget->columnCount(); j++) {
            vecItem.push_back( new QTableWidgetItem() );
        }

        int iColumnCnt = 0;
        vecItem[iColumnCnt++]->setText( msVecCodeStatDetailResult.at(i).first );
        vecItem[iColumnCnt++]->setData( Qt::DisplayRole, msVecCodeStatDetailResult.at(i).second.uiEffeCodeLines );
        vecItem[iColumnCnt++]->setData( Qt::DisplayRole, msVecCodeStatDetailResult.at(i).second.uiCommentCodeLines );
        vecItem[iColumnCnt++]->setData( Qt::DisplayRole, msVecCodeStatDetailResult.at(i).second.uiEmptyLineNum );
        vecItem[iColumnCnt++]->setData( Qt::DisplayRole, msVecCodeStatDetailResult.at(i).second.uiTotalLineNum );

        for ( int j=0; j<iColumnCnt; j++) {
            ui->tableWidget->setItem( i, j, vecItem.at(j) );
        }
    }
}



/**
 *  @fn     CodeStatisticsWindow::codeStatProgressUpdate(uint32_t ulCur, uint32_t ulTotal)
 *  @brief  代码统计窗口 进度更新
 *  @param  [in] ulCur      已扫描个数
 *  @param  [in] ulTotal    总个数
 *  @return 无
 */
void CodeStatisticsWindow::codeStatProgressUpdate(uint32_t ulCur, uint32_t ulTotal)
{
    mpProgressBar->setVisible( true );
    mpProgressBar->setValue( ulCur * 100 / ulTotal );
}



/**
 *  @fn     CodeStatisticsWindow::codeStatProgressDone(bool bStat)
 *  @brief  代码统计窗口 进度更新
 *  @param  [in] bStat  结束状态
 *  @return 无
 */
void CodeStatisticsWindow::codeStatProgressDone(bool bStat)
{
    mpLabelTotalTime->setText( tr("Time(s): ") + QString::number( mphTime->elapsed()/1000.0, 'f', 3) );
    delete mphTime;

    mpProgressBar->setVisible( false );

    mphCodeStat->codeStatResGet( msCodeStatResult );
    mphCodeStat->codeStatDetailResGet( msVecCodeStatDetailResult );

    mphCodeStat->codeStatResPrint( msCodeStatResult );

    codeStatTableWidgetUpdate();
    codeStatStatusBarUpdate();

    ui->pushButtonOk->setEnabled( true );

    if ( !bStat ) {
        QMessageBox::information( NULL, tr("Scan"), tr("Directory read fail"), QMessageBox::Cancel );
    }
}


/**
 *  @fn     CodeStatisticsWindow::on_pushButtonLookFor_clicked(void)
 *  @brief  代码统计窗口 浏览目录
 *  @return 无
 */
void CodeStatisticsWindow::on_pushButtonLookFor_clicked()
{
    QString str = QFileDialog::getExistingDirectory( this );

    ui->lineEditDir->setText( str );
}



/**
 *  @fn     CodeStatisticsWindow::on_pushButtonOk_clicked(void)
 *  @brief  代码统计窗口 统计代码
 *  @return 无
 */
void CodeStatisticsWindow::on_pushButtonOk_clicked()
{
    mphTime = new QTime();
    mphTime->start();

    ui->pushButtonOk->setEnabled( false );

    QStringList listStrFilter;

    mphFileFilterWindow->ffwFilterGet( listStrFilter );
    mphCodeStat->codeStatFilterSet( listStrFilter );

    mphCodeStat->codeStatProc( ui->lineEditDir->text() );
}



/**
 *  @fn     CodeStatisticsWindow::on_actionExit_triggered(void)
 *  @brief  代码统计窗口 关闭窗口
 *  @return 无
 */
void CodeStatisticsWindow::on_actionExit_triggered()
{
    this->close();
}



void CodeStatisticsWindow::on_actionAbout_triggered()
{
    QDesktopServices::openUrl ( QUrl::fromLocalFile("Version/Version.txt") );
}



void CodeStatisticsWindow::on_actionFilter_triggered()
{
    mphFileFilterWindow->show();
}


void CodeStatisticsWindow::on_actionSourceCode_triggered()
{
#define SOURCE_CODE_GITHUB_ADDR     ("git@github.com:coolweedman/CodeStatistics")

    int iRet;

    iRet = QMessageBox::information( this, tr("Copy GitHub Address"), SOURCE_CODE_GITHUB_ADDR, QMessageBox::Yes | QMessageBox::Cancel );

    if ( QMessageBox::Yes == iRet ) {
        QClipboard *pClipBoard = QApplication::clipboard();
        pClipBoard->setText( SOURCE_CODE_GITHUB_ADDR );
    }
}

void CodeStatisticsWindow::on_actionInstallation_triggered()
{
#define INSTALLATION_PACKAGE_ADDR   ( "http://pan.baidu.com/s/1dEKspTB" )

    int iRet;

    iRet = QMessageBox::information( this, tr("Copy Address"), INSTALLATION_PACKAGE_ADDR, QMessageBox::Yes | QMessageBox::Cancel );

    if ( QMessageBox::Yes == iRet ) {
        QClipboard *pClipBoard = QApplication::clipboard();
        pClipBoard->setText( INSTALLATION_PACKAGE_ADDR );
    }
}

void CodeStatisticsWindow::on_actionEnglish_triggered()
{
    CAppLanguage hLanguage;
    hLanguage.appLanguageSet( LANGUAGE_ENGLISH );
    QMessageBox::information( this, tr("Language Setting"), tr("Restart effect") );
}

void CodeStatisticsWindow::on_actionChinese_triggered()
{
    CAppLanguage hLanguage;
    hLanguage.appLanguageSet( LANGUAGE_CHINESE );
    QMessageBox::information( this, tr("Language Setting"), tr("Restart effect") );
}
