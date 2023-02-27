#ifndef PROFIL_H
#define PROFIL_H

#include <string>
#include "utilisateur.h"

class Profil
{
private:
    std::string nomProfil;
    Utilisateur* utilisateur;
public:
    Profil();
    Profil(Utilisateur* utilisateur, std::string nomProfil);
    ~Profil();

    std::string getNomProfil();
    Utilisateur* getUtilisateur();

    void setNomProfil(std::string nomProfil);
    void setUtilisateur(Utilisateur* utilisateur);

    bool operator==(const Profil &other) const;
};

#endif // PROFIL_H
