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
    ~Profil();

    std::string getNomProfil();

    void setNomProfil(std::string nomProfil);

    bool operator==(const Profil &profil1);
};

#endif // PROFIL_H
