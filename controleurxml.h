#ifndef CONTROLEURXML_H
#define CONTROLEURXML_H

#include "utilisateur.h"

#include <QtXml>
#include <iostream>

#define FILENAME "users.xml"

class ControleurXML
{
public:
    static std::vector<Utilisateur> parseFile();
    static bool writeFile(std::vector<Utilisateur>);
    static bool addUser(Utilisateur user);
    static Utilisateur* verifyUser(std::string login, std::string password);
    static int nombreUtilisateurs();
    static bool updateUser(const Utilisateur & oldUser, const Utilisateur & newUser);
private:
    static QDomDocument openDocument(std::string path);
    static Utilisateur createUserFromXMLComponent(QDomElement child);
};

#endif // CONTROLEURXML_H
