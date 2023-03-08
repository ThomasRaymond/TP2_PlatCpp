#include "profil.h"

Profil::Profil()
{
    this->nomProfil = "";
    this->databases.clear();
}

Profil::Profil(std::string nomProfil) {
    this->nomProfil = nomProfil;
}

Profil::~Profil(){
    nomProfil.clear();

    for(auto it = databases.begin(); it != databases.end(); it++){
        delete(*it);
    }
    databases.clear();
}

std::string Profil::getNomProfil() {
    return this->nomProfil;
}

QSqlDatabase* Profil::getDbByName(QString& nom){
    for (auto it = databases.begin(); it != databases.end(); it++){
        if ((*it)->databaseName() == nom){
            return (*it);
        }
    }
    return nullptr;
}

std::vector<QSqlDatabase*> Profil::getDbList(){
    return this->databases;
}

void Profil::addDataBase(QString& chemin){
    QSqlDatabase* _db = new QSqlDatabase(QSqlDatabase::addDatabase("QSQLITE"));
    _db->setDatabaseName(chemin);
    databases.push_back(_db);
}

void Profil::removeDbByName(QString& nom){
    for (auto it = databases.begin(); it != databases.end(); it++){
        if ((*it)->databaseName() == nom){
            remove(databases.begin(), databases.end(), *it);
            delete(*it);
        }
    }
}

void Profil::setNomProfil(std::string nomProfil){
    this->nomProfil = nomProfil;
}

bool Profil::operator==(const Profil &other) const {
    return this->nomProfil == other.nomProfil;
}
