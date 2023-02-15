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

    for (auto user: users) {
        std::cout << "user : " <<user.getPrenom() << std::endl;
    }

    return a.exec();
}
