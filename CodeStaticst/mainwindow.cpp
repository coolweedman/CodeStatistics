#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "filecodestatistics.h"
#include "dirscanstatistics.h"
#include <QDebug>
#include "codestatistics.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

#if 0
    CFileCodeStatistics *file = new CFileCodeStatistics( "a.txt" );
    file->fcsFileScan();
    file->fcsResultPrint();

    CDirScanStatistics *dir = new CDirScanStatistics();
    dir->dirFileFilterScan( "Statistics" );

    QVector<QString> vecStrFileName;
    dir->dirFileScanedGet( vecStrFileName );

    foreach (QString strFileName, vecStrFileName) {
        qDebug()<<strFileName;
    }
#endif

    CCodeStatistics *codeStat = new CCodeStatistics();
    codeStat->codeStatProc( "Statistics" );
}

MainWindow::~MainWindow()
{
    delete ui;
}
