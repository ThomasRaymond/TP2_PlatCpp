#include "profil.h"
#include "utilisateur.h"

Profil::Profil()
{
    this->nomProfil = "";
}

Profil::Profil(std::string nomProfil) {
    this->nomProfil = nomProfil;
}

Profil::~Profil() {
}

std::string Profil::getNomProfil() {
    return this->nomProfil;
}


void Profil::setNomProfil(std::string nomProfil){
    this->nomProfil = nomProfil;
}

bool Profil::operator==(const Profil &profil){
    if(this->getNomProfil() == profil.getNomProfil()){
        return true;
    }
    else{
        return false;
    }
}

