#ifndef UTILISATEUR_H
#define UTILISATEUR_H


#include <string>
#include <vector>
#include "profil.h"

#define READ 0
#define WRITE 1
#define DELETE 2

class Utilisateur
{
private:
    std::string nom;
    std::string prenom;
    std::string mail;
    std::string mdp;
    std::vector<Profil> profils;
    std::vector<bool> permissions;  // (Lecture, Ecriture, Suppression)
public:
    Utilisateur();
    Utilisateur(std::string nom, std::string prenom, std::string mail, std::string mdp);

    std::string getNom();
    std::string getPrenom();
    std::string getMail();
    std::string getPassword();
    std::vector<Profil> getProfils();
    std::vector<bool> getPermissions();

    bool can(int droit);

    void setNom(std::string nom);
    void setPrenom(std::string prenom);
    void setMail(std::string mail);
    void setPassword(std::string mdp);

    bool addProfil(Profil profil);
    bool removeProfil(Profil profil);

    bool addPermission(int permission);
    bool removePermission(int permission);


    bool operator==(Utilisateur other);
};

#endif // UTILISATEUR_H
