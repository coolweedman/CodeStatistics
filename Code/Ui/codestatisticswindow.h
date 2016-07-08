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
    Ui::CodeStatisticsWindow *ui;

    QLabel  *mpLabelEffeLine;
    QLabel  *mpLabelCommentLine;
    QLabel  *mpLabelEmptyLine;
    QLabel  *mpLabelTotalLine;
};

#endif // CODESTATISTICSWINDOW_H
