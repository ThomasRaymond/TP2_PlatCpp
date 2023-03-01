#include "profil.h"

Profil::Profil()
{
    this->nomProfil = "";
}

Profil::Profil(std::string nomProfil) {
    this->nomProfil = nomProfil;
}

std::string Profil::getNomProfil() {
    return this->nomProfil;
}

void Profil::setNomProfil(std::string nomProfil){
    this->nomProfil = nomProfil;
}

bool Profil::operator==(const Profil &other) const {
    return this->nomProfil == other.nomProfil;
}
