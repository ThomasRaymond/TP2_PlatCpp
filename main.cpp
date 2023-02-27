#include "inscription.h"
#include "controleurbdd.h"
#include "connexion.h"
#include "controleurxml.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include <iostream>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    auto users = ControleurXML::parseFile();
    ControleurXML::writeFile(users);


    return a.exec();
}
