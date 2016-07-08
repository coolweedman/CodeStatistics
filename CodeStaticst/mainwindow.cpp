#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "filecodestatistics.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    CFileCodeStatistics *file = new CFileCodeStatistics( "a.txt" );
    file->fcsFileScan();
    file->fcsResultPrint();
}

MainWindow::~MainWindow()
{
    delete ui;
}
