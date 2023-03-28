#ifndef CONTROLEURXML_H
#define CONTROLEURXML_H

#include "utilisateur.h"

#include <QtXml>
#include <iostream>

#define FILENAME "users.xml"

// Classe permettant de gérer les utilisateurs et les génération de fichiers XML
class ControleurXML
{
public:
    static std::vector<Utilisateur>& parseFile();
    static bool writeFile();
    static bool addUser(Utilisateur user);
    static Utilisateur* verifyUser(std::string login, std::string password);
    static int nombreUtilisateurs();
    static bool updateUser(const Utilisateur & oldUser);
    static std::vector<Utilisateur> listeUtilisateurs;
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
