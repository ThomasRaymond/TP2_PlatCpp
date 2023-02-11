#ifndef UTILISATEUR_H
#define UTILISATEUR_H


#include <string>
#include <vector>
#include "droitsutilisateurs.h"
class Utilisateur
{
private:
    std::string nom;
    std::string prenom;
    std::string mail;
    std::vector<DroitsUtilisateurs> permissions;
public:
    Utilisateur();
    Utilisateur(std::string nom, std::string prenom, std::string mail, std::vector<DroitsUtilisateurs> permissions);
    ~Utilisateur();

    std::string getNom();
    std::string getPrenom();
    std::string getMail();
    std::vector<DroitsUtilisateurs> getPermissions();

    void setNom(std::string nom);
    void setPrenom(std::string prenom);
    void setMail(std::string mail);
    void addPermission(DroitsUtilisateurs permission);
    void removePermission(DroitsUtilisateurs permissions);
};

#endif // UTILISATEUR_H
