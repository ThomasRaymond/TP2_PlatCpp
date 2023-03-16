#ifndef CONTROLEURXML_H
#define CONTROLEURXML_H

#include "utilisateur.h"

#include <QtXml>
#include <iostream>

//#define FILENAME "users.xml"
#define FILENAME "test.xml"

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

    static QDomElement QDomElemFromUtilisateur(Utilisateur & user, QDomDocument & document);
    static Utilisateur UtilisateurFromQDom(QDomElement & qdom);
    static QDomElement QDomElemFromProfil(Profil & profil, QDomDocument & document);
    static Profil ProfilFromQDom(QDomElement & qdom);
    static QDomElement QDomElemFromDatabase(QSqlDatabase & database, QDomDocument & document);
    static QSqlDatabase DatabaseFromQDom(QDomElement & qdom);
};

#endif // CONTROLEURXML_H
