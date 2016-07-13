#ifndef FILEFILTERWINDOW_H
#define FILEFILTERWINDOW_H

#include <QMainWindow>

namespace Ui {
class FileFilterWindow;
}

struct SFileFilterStru {
    bool bC;
    bool bH;
    bool bCpp;
    bool bJava;
    bool bCs;
    bool bTxt;
    bool bOther;

    QString strOtherText;
};

class FileFilterWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit FileFilterWindow(QWidget *parent = 0);
    ~FileFilterWindow();

signals:
    void ffwFilterSig(QVector<QString> &rVecStrFilter);

protected:
    void ffwSave(void);
    void ffwReStore(void);

    void ffwUi2Stru(void);
    void ffwStru2Ui(void);

    void ffwSetting2Stru(void);
    void ffwStru2Setting(void);

    void ffwStru2String(void);

public:
    void ffwFilterGet(QStringList &rFilter);

private slots:
    void on_checkBoxOther_toggled(bool checked);
    void on_pushButtonOk_clicked();
    void on_pushButtonCancel_clicked();

private:
    Ui::FileFilterWindow   *ui;
    QVector<QString>       *mpVecStrFileFilter;
    SFileFilterStru         msFileFilterStru;
};

#endif // FILEFILTERWINDOW_H
