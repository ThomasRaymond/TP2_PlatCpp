#ifndef PROFIL_H
#define PROFIL_H

#include <string>
#include <QtSql>

// Classe permettant de définir un profil
class Profil
{
private:
    std::string nomProfil;
    std::vector<QSqlDatabase> databases;
public:
    Profil();
    Profil(std::string nomProfil);

    void setNomProfil(std::string nomProfil);
    const std::string getNomProfil();

    std::vector<QSqlDatabase> & getDatabases() {return databases;}

    bool operator==(const Profil &other) const;
};

#endif // PROFIL_H
