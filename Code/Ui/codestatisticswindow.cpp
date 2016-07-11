#include "codestatisticswindow.h"
#include "ui_codestatisticswindow.h"
#include <QFileDialog>
#include <QLabel>

CodeStatisticsWindow::CodeStatisticsWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CodeStatisticsWindow)
{
    ui->setupUi(this);

    mpLabelEffeLine    = new QLabel();
    mpLabelCommentLine = new QLabel();
    mpLabelEmptyLine   = new QLabel();
    mpLabelTotalLine   = new QLabel();
    mpLabelTotalFiles  = new QLabel();

    statusBar()->addWidget( mpLabelEffeLine );
    statusBar()->addWidget( mpLabelCommentLine );
    statusBar()->addWidget( mpLabelEmptyLine );
    statusBar()->addWidget( mpLabelTotalLine );
    statusBar()->addWidget( mpLabelTotalFiles );

    mpLabelEffeLine->setText( "Effe: ?" );
    mpLabelCommentLine->setText( "Comment: ?" );
    mpLabelEmptyLine->setText( "Empty: ?" );
    mpLabelTotalLine->setText( "Total: ?" );
    mpLabelTotalFiles->setText( "File(s): ?" );
}

CodeStatisticsWindow::~CodeStatisticsWindow()
{
    delete ui;
}

void CodeStatisticsWindow::codeStatStatusBarUpdate(void)
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
        ui->tableWidget->setItem( i, 1, new QTableWidgetItem( QString::number(msVecCodeStatDetailResult.at(i).second.uiEffeCodeLines) ) );
        ui->tableWidget->setItem( i, 2, new QTableWidgetItem( QString::number(msVecCodeStatDetailResult.at(i).second.uiCommentCodeLines) ) );
        ui->tableWidget->setItem( i, 3, new QTableWidgetItem( QString::number(msVecCodeStatDetailResult.at(i).second.uiEmptyLineNum) ) );
        ui->tableWidget->setItem( i, 4, new QTableWidgetItem( QString::number(msVecCodeStatDetailResult.at(i).second.uiTotalLineNum) ) );
    }
}

void CodeStatisticsWindow::codeStatTableWidgetUpdate(void)
{
    mpLabelEffeLine->setText( " Effe: " + QString::number(msCodeStatResult.uiEffeCodeLines) );
    mpLabelCommentLine->setText( " Comment: " + QString::number(msCodeStatResult.uiCommentCodeLines) );
    mpLabelEmptyLine->setText( " Empty: " + QString::number(msCodeStatResult.uiEmptyLineNum) );
    mpLabelTotalLine->setText( " Total: " + QString::number(msCodeStatResult.uiTotalLineNum) );
    mpLabelTotalFiles->setText( " File(s): " + QString::number(msVecCodeStatDetailResult.length()) );
}

void CodeStatisticsWindow::on_pushButtonLookFor_clicked()
{
    QString str = QFileDialog::getExistingDirectory( this );

    ui->lineEditDir->setText( str );
}

void CodeStatisticsWindow::on_pushButtonOk_clicked()
{
    CCodeStatistics *phCodeStat = new CCodeStatistics();
    phCodeStat->codeStatProc( ui->lineEditDir->text() );

    msVecCodeStatDetailResult.clear();
    phCodeStat->codeStatResGet( msCodeStatResult );
    phCodeStat->codeStatDetailResGet( msVecCodeStatDetailResult );

    phCodeStat->codeStatResPrint( msCodeStatResult );

    codeStatTableWidgetUpdate();
    codeStatStatusBarUpdate();
}
