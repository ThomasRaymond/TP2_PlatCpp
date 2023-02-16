#include "inscription.h"
#include "controleurbdd.h"
#include "connexion.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include <iostream>

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


    MainWindow* main = new MainWindow();
    main->show();

    ControleurBDD cBDD;
    if (cBDD.nombreUtilisateurs()>1){
        Connexion conn(main);
        conn.exec();
    }
    else {
        Inscription i(main);
        i.exec();
    }

    return a.exec();
}
