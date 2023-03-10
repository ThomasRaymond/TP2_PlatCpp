#include "profil.h"

Profil::Profil()
{
    this->nomProfil = "";
    this->databases.clear();
}

Profil::Profil(std::string nomProfil) {
    this->nomProfil = nomProfil;
}

const std::string Profil::getNomProfil() {
    return this->nomProfil;
}

void Profil::setNomProfil(std::string nomProfil){
    this->nomProfil = nomProfil;
}

bool Profil::operator==(const Profil &other) const {
    return this->nomProfil == other.nomProfil;
}
