#ifndef UTILISATEUR_H
#define UTILISATEUR_H


#include <string>
#include <vector>
#include "profil.h"
#include "droitsutilisateurs.h"

class Utilisateur
{
private:
    std::string nom;
    std::string prenom;
    std::string mail;
    std::vector<DroitsUtilisateurs> permissions;
    std::vector<Profil> profils;
public:
    Utilisateur();
    Utilisateur(std::string nom, std::string prenom, std::string mail, std::vector<DroitsUtilisateurs> permissions, std::vector<Profil> profils);
    ~Utilisateur();

    std::string getNom();
    std::string getPrenom();
    std::string getMail();
    std::vector<DroitsUtilisateurs> getPermissions();
    std::vector<Profil> getProfils();

    void setNom(std::string nom);
    void setPrenom(std::string prenom);
    void setMail(std::string mail);
    void addPermission(DroitsUtilisateurs permission);
    void removePermission(DroitsUtilisateurs permissions);
    void addProfil(Profil profil);
    void removeProfil(Profil profil);
};

#endif // UTILISATEUR_H
