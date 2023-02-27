#include "utilisateur.h"
#include <algorithm>

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

Utilisateur::~Utilisateur(){
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

std::string Utilisateur::getPassword(){
    return this->mdp;
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

void Utilisateur::setMail(std::string mail){
    this->mail = mail;
}

void Utilisateur::setPassword(std::string mdp){
    this->mdp = mdp;
}

void Utilisateur::addPermission(DroitsUtilisateurs permission) {
    if (std::find(this->permissions.begin(), this->permissions.end(), permission) != this->permissions.end()){
        this->permissions.push_back(permission);
    }
}

void Utilisateur::removePermission(DroitsUtilisateurs permission){
    if (std::find(this->permissions.begin(), this->permissions.end(), permission) == this->permissions.end()){
        remove(this->permissions.begin(), this->permissions.end(), permission);
    }
}

