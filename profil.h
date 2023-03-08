#ifndef PROFIL_H
#define PROFIL_H

#include <string>
#include <QtSql>

class Profil
{
private:
    std::string nomProfil;
    std::vector<QSqlDatabase*> databases;
public:
    Profil();
    Profil(std::string nomProfil);
    ~Profil();

    std::string getNomProfil();
    QSqlDatabase* getDbByName(QString& nom);
    std::vector<QSqlDatabase*> getDbList();

    void addDataBase(QString& chemin);
    void removeDbByName(QString& nom);

    void setNomProfil(std::string nomProfil);

    bool operator==(const Profil &other) const;
};

#endif // PROFIL_H
