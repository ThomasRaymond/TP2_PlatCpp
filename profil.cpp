#include "profil.h"

Profil::Profil()
{
    this->nomProfil = "";
    this->databases.clear();
}

Profil::Profil(std::string nomProfil) {
    this->nomProfil = nomProfil;
}

std::string Profil::getNomProfil() {
    return this->nomProfil;
}

QSqlDatabase* Profil::getDbByName(QString& name){
    for (auto it = databases.begin(); it != databases.end(); it++){
        if ((*it)->databaseName() == name){
            return (*it);
        }
    }
    return nullptr;
}

void Profil::addDataBase(QString& chemin){
    QSqlDatabase* _db = new QSqlDatabase();
    _db->setDatabaseName(chemin);
    databases.push_back(_db);
}

void Profil::setNomProfil(std::string nomProfil){
    this->nomProfil = nomProfil;
}

bool Profil::operator==(const Profil &other) const {
    return this->nomProfil == other.nomProfil;
}
