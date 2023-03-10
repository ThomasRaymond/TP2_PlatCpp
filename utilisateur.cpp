#include "utilisateur.h"
#include <algorithm>
#include <iostream>

Utilisateur::Utilisateur()
{
    this->profils = std::vector<Profil>();
    this->permissions = std::vector<bool>(3, false);
}

Utilisateur::Utilisateur(std::string nom, std::string prenom, std::string mail, std::string mdp)
{
    this->nom = nom;
    this->prenom = prenom;
    this->mail = mail;
    this->mdp = mdp;
    this->permissions = std::vector<bool>(3, false);
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

std::vector<Profil> Utilisateur::getProfils()
{
    return this->profils;
}

std::vector<bool> Utilisateur::getPermissions()
{
    return this->permissions;
}

bool Utilisateur::can(int droit)
{
    return this->permissions.at(droit) == true;
}

void Utilisateur::setNom(std::string nom)
{
    this->nom = nom;
}

void Utilisateur::setPrenom(std::string prenom)
{
    this->prenom = prenom;
}

void Utilisateur::setMail(std::string mail)
{
    this->mail = mail;
}

void Utilisateur::setPassword(std::string mdp)
{
    this->mdp = mdp;
}

bool Utilisateur::addProfil(Profil profil)
{
    auto pos = std::find(this->profils.begin(), this->profils.end(), profil);

    if (pos == this->profils.end())
    {
        this->profils.push_back(profil);
        return true;
    }
    return false;
}

bool Utilisateur::removeProfil(Profil profil)
{
    auto pos = std::find(this->profils.begin(), this->profils.end(), profil);

    if (pos != this->profils.end())
    {
        this->profils.erase(pos);
        return true;
    }
    return false;
}

bool Utilisateur::addPermission(int permission) {
    if (!this->can(permission))
    {
        this->permissions.at(permission) = true;
        return true;
    }
    return false;
}

bool Utilisateur::removePermission(int permission){
    if (this->can(permission))
    {
        this->permissions.at(permission) = false;
        return true;
    }
    return false;
}

bool Utilisateur::operator==(Utilisateur other) {
    if (this->getMail() != other.getMail())
    {
        return false;
    }
    return true;
}
