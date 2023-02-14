#include "inscription.h"
#include "controleurbdd.h"
#include "connexion.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include <iostream>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    /*
    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "TP2_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }

    ControleurBDD BDDc = ControleurBDD();

    std::cout << "start" << std::endl;

    if (BDDc.nombreUtilisateurs() > 1) {
        std::cout << "1";
        Connexion c;
        c.show();
    }else{
        std::cout << "2";
        Inscription i;
        i.show();
    }
    */

    Inscription i;
    i.show();

    return a.exec();
}
