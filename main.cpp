#include "mainwindow.h"
#include "inscription.h"
#include "controleurbdd.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "TP2_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }

    if (ControleurBDD::nombreUtilisateurs() > 1) {
        // Connection c;
        // c.show();
    }else{
        Inscription i;
        i.show();
    }
    return a.exec();
}
