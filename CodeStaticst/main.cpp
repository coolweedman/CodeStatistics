#include "codestatisticswindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    CodeStatisticsWindow w;
    w.show();

    return a.exec();
}
