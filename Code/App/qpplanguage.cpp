#include "applanguage.h"
#include <QSettings>


#define LANGUAGE_SEETING_FILE_NAME  ( "Cfg/Language.ini" )
#define LANGUAGE_CFG_LANGUAGE       ( "Language" )

#define LANGUAGE_ENGLISH_FILE_NAME  ( "Language/English.qm" )
#define LANGUAGE_CHINESE_FILE_NAME  ( "Language/Chinese.qm" )


CAppLanguage::CAppLanguage(void)
{
    appLanguageReStore();
}


CAppLanguage::~CAppLanguage(void)
{
    appLanguageSave();
}

void CAppLanguage::appLanguageSet(EAppLanguage eLanguage)
{
    meLanguege = eLanguage;
}

QString CAppLanguage::appLanguageGet(void)
{
    QString strLanguage;

    switch ( meLanguege ) {
    case LANGUAGE_ENGLISH:
        strLanguage = LANGUAGE_ENGLISH_FILE_NAME;
        break;

    case LANGUAGE_CHINESE:
        strLanguage = LANGUAGE_CHINESE_FILE_NAME;
        break;

    default:
        strLanguage = "";
        break;
    }

    return strLanguage;
}

void CAppLanguage::appLanguageSave(void)
{
    QSettings *pSetting = new QSettings( LANGUAGE_SEETING_FILE_NAME, QSettings::IniFormat );

    pSetting->setValue( LANGUAGE_CFG_LANGUAGE, (int)meLanguege );

    delete pSetting;
}

void CAppLanguage::appLanguageReStore(void)
{
    QSettings *pSetting = new QSettings( LANGUAGE_SEETING_FILE_NAME, QSettings::IniFormat );

    meLanguege = (EAppLanguage)pSetting->value( LANGUAGE_CFG_LANGUAGE, (int)LANGUAGE_ENGLISH ).toInt();

    delete pSetting;
}

