#include "utilisateur.h"

Utilisateur::Utilisateur()
{
    this->permissions = std::vector<DroitsUtilisateurs>(3);
}

Utilisateur::Utilisateur(std::string nom, std::string prenom, std::string mail, std::vector<DroitsUtilisateurs> permissions){
    this->nom = nom;
    this->prenom = prenom;
    this->mail = mail;
    this->permissions = std::vector<DroitsUtilisateurs>(permissions);
}

std::string Utilisateur::getNom(){
    return this->nom;
}

std::string Utilisateur::getPrenom(){
    return this->prenom;
}

std::string Utilisateur::getMail(){
    return this->mail;
}

std::vector<DroitsUtilisateurs> Utilisateur::getPermissions(){
    return this->permissions;
}

void Utilisateur::setNom(std::string nom){
    this->nom = nom;
}

void Utilisateur::setPrenom(std::string prenom){
    this->prenom = prenom;
}
