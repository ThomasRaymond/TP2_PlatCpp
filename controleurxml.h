#ifndef CONTROLEURXML_H
#define CONTROLEURXML_H

#include "utilisateur.h"

#include <QtXml>
#include <iostream>

class ControleurXML
{
public:
    static std::vector<Utilisateur> parseFile();
    static bool writeFile(std::vector<Utilisateur>);
private:
    static QDomDocument openDocument(std::string path);
    static Utilisateur createUserFromXMLComponent(QDomElement child);
};

#endif // CONTROLEURXML_H
