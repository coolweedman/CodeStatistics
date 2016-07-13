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

/**********************************************************************************************************
  宏定义
**********************************************************************************************************/

#define CODE_STAT_VERSION           ( 102 )



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

    this->setWindowTitle( "Code Statistics V" + QString::number( CODE_STAT_VERSION/100.0, 'f', 2 ) );

    mphFileFilterWindow = new FileFilterWindow(this);
}



/**
 *  @fn     CodeStatisticsWindow::~CodeStatisticsWindow(QWidget *parent)
 *  @brief  代码统计窗口 析构函数
 *  @return 无
 */
CodeStatisticsWindow::~CodeStatisticsWindow()
{
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

    mpLabelEffeLine->setText( "Effe: ?" );
    mpLabelCommentLine->setText( "Comment: ?" );
    mpLabelEmptyLine->setText( "Empty: ?" );
    mpLabelTotalLine->setText( "Total: ?" );
    mpLabelTotalFiles->setText( "File(s): ?" );

    statusBar()->addWidget( mpLabelEffeLine );
    statusBar()->addWidget( mpLabelCommentLine );
    statusBar()->addWidget( mpLabelEmptyLine );
    statusBar()->addWidget( mpLabelTotalLine );

    statusBar()->addWidget( mpLabelTotalFiles );
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
    mpLabelEffeLine->setText( " Effe: " + QString::number(msCodeStatResult.uiEffeCodeLines) );
    mpLabelCommentLine->setText( " Comment: " + QString::number(msCodeStatResult.uiCommentCodeLines) );
    mpLabelEmptyLine->setText( " Empty: " + QString::number(msCodeStatResult.uiEmptyLineNum) );
    mpLabelTotalLine->setText( " Total: " + QString::number(msCodeStatResult.uiTotalLineNum) );
    mpLabelTotalFiles->setText( " File(s): " + QString::number(msVecCodeStatDetailResult.length()) );
}



/**
 *  @fn     CodeStatisticsWindow::codeStatTableWidgetUpdate(void)
 *  @brief  代码统计窗口 详细信息更新
 *  @return 无
 */
void CodeStatisticsWindow::codeStatTableWidgetUpdate(void)
{
    while ( ui->tableWidget->rowCount() > 0 ) {
        delete ui->tableWidget->itemAt( 0, 0 );
        delete ui->tableWidget->itemAt( 0, 1 );
        delete ui->tableWidget->itemAt( 0, 2 );
        delete ui->tableWidget->itemAt( 0, 3 );
        delete ui->tableWidget->itemAt( 0, 4 );

        ui->tableWidget->removeRow( 0 );
    }

    ui->tableWidget->setRowCount( msVecCodeStatDetailResult.length() );
    for ( int i=0; i<msVecCodeStatDetailResult.length(); i++ ) {
        ui->tableWidget->setItem( i, 0, new QTableWidgetItem(msVecCodeStatDetailResult.at(i).first) );
        ui->tableWidget->setItem( i, 1, new QTableWidgetItem(QString::number(msVecCodeStatDetailResult.at(i).second.uiEffeCodeLines) ) );
        ui->tableWidget->setItem( i, 2, new QTableWidgetItem( QString::number(msVecCodeStatDetailResult.at(i).second.uiCommentCodeLines) ) );
        ui->tableWidget->setItem( i, 3, new QTableWidgetItem( QString::number(msVecCodeStatDetailResult.at(i).second.uiEmptyLineNum) ) );
        ui->tableWidget->setItem( i, 4, new QTableWidgetItem( QString::number(msVecCodeStatDetailResult.at(i).second.uiTotalLineNum) ) );
    }
}


void CodeStatisticsWindow::codeStatProgressUpdate(uint32_t ulCur, uint32_t ulTotal)
{
    mpProgressBar->setVisible( true );
    mpProgressBar->setValue( ulCur * 100 / ulTotal );
}


void CodeStatisticsWindow::codeStatProgressDone(void)
{
    mpProgressBar->setVisible( false );
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
    QStringList listStrFilter;

    CCodeStatistics *phCodeStat = new CCodeStatistics();
    mphFileFilterWindow->ffwFilterGet( listStrFilter );
    phCodeStat->codeStatFilterSet( listStrFilter );

    connect( phCodeStat,
             SIGNAL(codeStatProgressSig(uint32_t,uint32_t)),
             this,
             SLOT(codeStatProgressUpdate(uint32_t,uint32_t)) );
    connect( phCodeStat,
             SIGNAL(codeStatDoneSig()),
             this,
             SLOT(codeStatProgressDone()) );

    phCodeStat->codeStatProc( ui->lineEditDir->text() );

    msVecCodeStatDetailResult.clear();
    phCodeStat->codeStatResGet( msCodeStatResult );
    phCodeStat->codeStatDetailResGet( msVecCodeStatDetailResult );

    phCodeStat->codeStatResPrint( msCodeStatResult );

    codeStatTableWidgetUpdate();
    codeStatStatusBarUpdate();
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

/**********************************************************************************************************
  END FILE
**********************************************************************************************************/
