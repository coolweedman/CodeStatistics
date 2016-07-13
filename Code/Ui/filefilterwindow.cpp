#include "filefilterwindow.h"
#include "ui_filefilterwindow.h"
#include <QSettings>
#include <QDebug>

#define FFW_CFG_FILE_NAME           ( "Cfg/FileFilter.ini" )

#define FFW_CFG_FILE_C              ( "C" )
#define FFW_CFG_FILE_H              ( "H" )
#define FFW_CFG_FILE_CPP            ( "CPP" )
#define FFW_CFG_FILE_JAVA           ( "JAVA" )
#define FFW_CFG_FILE_CS             ( "CS" )
#define FFW_CFG_FILE_TXT            ( "TXT" )
#define FFW_CFG_FILE_OTHER          ( "OHTER" )
#define FFW_CFG_FILE_TEXT           ( "TEXT" )



FileFilterWindow::FileFilterWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FileFilterWindow)
{
    ui->setupUi(this);

    mpVecStrFileFilter = new QVector<QString>();

    ffwReStore();
}

FileFilterWindow::~FileFilterWindow()
{
    ffwSave();

    delete ui;
}

void FileFilterWindow::ffwSave(void)
{
    ffwUi2Stru();
    ffwStru2Setting();
}

void FileFilterWindow::ffwReStore(void)
{
    ffwSetting2Stru();
    ffwStru2Ui();
    ffwStru2String();
}

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
