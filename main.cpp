#include "controleurbdd.h"
#include "connexion.h"
#include "controleurxml.h"
#include "mainwindow.h"


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
    main->init();

    return a.exec();
}
