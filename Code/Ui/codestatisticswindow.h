#ifndef CODESTATISTICSWINDOW_H
#define CODESTATISTICSWINDOW_H

#include <QMainWindow>
#include "codestatistics.h"

namespace Ui {
class CodeStatisticsWindow;
}

class QLabel;


class CodeStatisticsWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit CodeStatisticsWindow(QWidget *parent = 0);
    ~CodeStatisticsWindow();

private slots:
    void on_pushButtonLookFor_clicked();
    void on_pushButtonOk_clicked();

private:
    void codeStatStatusBarUpdate(void);
    void codeStatTableWidgetUpdate(void);

private:
    Ui::CodeStatisticsWindow   *ui;
    SCodeStatResultStru         msCodeStatResult;

    QVector<QPair<QString, SCodeStatResultStru> > msVecCodeStatDetailResult;

    QLabel  *mpLabelEffeLine;
    QLabel  *mpLabelCommentLine;
    QLabel  *mpLabelEmptyLine;
    QLabel  *mpLabelTotalLine;

    QLabel  *mpLabelTotalFiles;
};

#endif // CODESTATISTICSWINDOW_H
