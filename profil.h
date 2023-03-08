#ifndef PROFIL_H
#define PROFIL_H

#include <string>
#include <QtSql>

class Profil
{
private:
    std::string nomProfil;
    std::vector<QSqlDatabase> databases;
public:
    Profil();
    Profil(std::string nomProfil);

    std::string getNomProfil();

    std::vector<QSqlDatabase> & getDatabases() {return databases;}
    const std::vector<QSqlDatabase> & getDatabases() const {return databases;}

    void setNomProfil(std::string nomProfil);

    bool operator==(const Profil &other) const;
};

#endif // PROFIL_H
