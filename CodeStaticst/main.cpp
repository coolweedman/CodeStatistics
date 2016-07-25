#include "codestatisticswindow.h"
#include <QApplication>
#include <windows.h>
#include "applanguage.h"
#include <QTranslator>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    CAppLanguage *phLanguage = new CAppLanguage();
    QTranslator *pTrans = new QTranslator;
    pTrans->load( phLanguage->appLanguageGet() );
    app.installTranslator( pTrans );
    delete phLanguage;

    CodeStatisticsWindow hWin;
    hWin.show();

    return app.exec();
}
