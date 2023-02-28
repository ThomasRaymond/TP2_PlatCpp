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
    std::string mdp;
    std::vector<DroitsUtilisateurs> permissions;
public:
    Utilisateur();
    Utilisateur(std::string nom, std::string prenom, std::string mail, std::vector<DroitsUtilisateurs> permissions);
    ~Utilisateur();

    std::string getNom();
    std::string getPrenom();
    std::string getMail();
    std::string getPassword();
    std::vector<DroitsUtilisateurs> getPermissions();

    void setNom(std::string nom);
    void setPrenom(std::string prenom);
    void setMail(std::string mail);
    void setPassword(std::string mdp);
    void addPermission(DroitsUtilisateurs permission);
    void removePermission(DroitsUtilisateurs permissions);

    bool operator==(Utilisateur other);
};

#endif // UTILISATEUR_H
