#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "filecodestatistics.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    CFileCodeStatistics *file = new CFileCodeStatistics( "a.txt" );
    if ( NULL != file ) {
        file->fcsFileScan();
        file->fcsResultPrint();

        delete file;
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
