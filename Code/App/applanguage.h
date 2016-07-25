#ifndef APPLANGUAGE
#define APPLANGUAGE

#include <QObject>

enum EAppLanguage {
    LANGUAGE_ENGLISH = 0,
    LANGUAGE_CHINESE,
};

class CAppLanguage : QObject {
    Q_OBJECT

public:
    CAppLanguage(void);
   ~CAppLanguage(void);

public:
    void appLanguageSet(EAppLanguage eLanguage);
    QString appLanguageGet(void);

private:
    void appLanguageSave(void);
    void appLanguageReStore(void);

private:
    EAppLanguage    meLanguege;
};

#endif // APPLANGUAGE

