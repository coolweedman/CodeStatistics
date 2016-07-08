#include "codestatisticswindow.h"
#include "ui_codestatisticswindow.h"
#include <QFileDialog>
#include <QLabel>

CodeStatisticsWindow::CodeStatisticsWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CodeStatisticsWindow)
{
    ui->setupUi(this);

    mpLabelEffeLine = new QLabel();
    mpLabelCommentLine = new QLabel();
    mpLabelEmptyLine = new QLabel();
    mpLabelTotalLine = new QLabel();

    statusBar()->addWidget( mpLabelEffeLine );
    statusBar()->addWidget( mpLabelCommentLine );
    statusBar()->addWidget( mpLabelEmptyLine );
    statusBar()->addWidget( mpLabelTotalLine );

    mpLabelEffeLine->setText( "Effe: ?" );
    mpLabelCommentLine->setText( "Comment: ?" );
    mpLabelEmptyLine->setText( "Empty: ?" );
    mpLabelTotalLine->setText( "Total: ?" );
}

CodeStatisticsWindow::~CodeStatisticsWindow()
{
    delete ui;
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

    SCodeStatResultStru sStru;
    phCodeStat->codeStatResGet( sStru );
    phCodeStat->codeStatResPrint( sStru );

    mpLabelEffeLine->setText( "Effe: " + QString::number(sStru.uiEffeCodeLines) );
    mpLabelCommentLine->setText( "Comment: " + QString::number(sStru.uiCommentCodeLines) );
    mpLabelEmptyLine->setText( "Empty: " + QString::number(sStru.uiEmptyLineNum) );
    mpLabelTotalLine->setText( "Total: " + QString::number(sStru.uiTotalLineNum) );
}
