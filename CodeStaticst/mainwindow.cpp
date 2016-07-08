#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "filecodestatistics.h"
#include "dirscanstatistics.h"
#include <QDebug>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

#if 0
    CFileCodeStatistics *file = new CFileCodeStatistics( "a.txt" );
    file->fcsFileScan();
    file->fcsResultPrint();
#endif

    CDirScanStatistics *dir = new CDirScanStatistics();
    dir->dirFileFilterScan( "Statistics" );

    QVector<QString> vecStrFileName;
    dir->dirFileScanedGet( vecStrFileName );

    foreach (QString strFileName, vecStrFileName) {
        qDebug()<<strFileName;
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
