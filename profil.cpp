#include "profil.h"

Profil::Profil()
{
    this->nomProfil = "";
    this->utilisateur = nullptr;
}

Profil::Profil(Utilisateur* utilisateur, std::string nomProfil) {
    this->nomProfil = nomProfil;
    this->utilisateur = utilisateur;
}

Profil::~Profil() {
    this->utilisateur = nullptr;
}

std::string Profil::getNomProfil() {
    return this->nomProfil;
}

Utilisateur* Profil::getUtilisateur(){
    return this->utilisateur;
}

void Profil::setNomProfil(std::string nomProfil){
    this->nomProfil = nomProfil;
}

void Profil::setUtilisateur(Utilisateur* utilisateur) {
    this->utilisateur = utilisateur;
}

bool Profil::operator==(const Profil &other) const {
    return this->nomProfil == other.nomProfil;
}
