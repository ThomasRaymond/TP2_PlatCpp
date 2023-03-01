#ifndef PROFIL_H
#define PROFIL_H

#include <string>

class Profil
{
private:
    std::string nomProfil;
public:
    Profil();
    Profil(std::string nomProfil);

    std::string getNomProfil();

    void setNomProfil(std::string nomProfil);

    bool operator==(const Profil &other) const;
};

#endif // PROFIL_H
