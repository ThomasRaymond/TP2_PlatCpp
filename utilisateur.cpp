#include "utilisateur.h"
#include <algorithm>
#include <iostream>

// Constructeur par défaut
/*
    * @brief Constructeur par défaut de la classe Utilisateur
*/
Utilisateur::Utilisateur()
{
    this->profils = std::vector<Profil>();
    this->permissions = std::vector<bool>(3, false);
}

// Constructeur
/*
    * @brief Constructeur de la classe Utilisateur
    * @param nom : nom de l'utilisateur
    * @param prenom : prénom de l'utilisateur
    * @param mail : mail de l'utilisateur
    * @param mdp : mot de passe de l'utilisateur
*/
Utilisateur::Utilisateur(std::string nom, std::string prenom, std::string mail, std::string mdp)
{
    this->nom = nom;
    this->prenom = prenom;
    this->mail = mail;
    this->mdp = mdp;
    this->permissions = std::vector<bool>(3, false);
}

/*
    * @brief Getter du nom de l'utilisateur
    * @return nom : std::string
*/
std::string Utilisateur::getNom(){
    return this->nom;
}

/*
    * @brief Getter du prénom de l'utilisateur
    * @return prenom : std::string
*/
std::string Utilisateur::getPrenom(){
    return this->prenom;
}

/*
    * @brief Getter du mail de l'utilisateur
    * @return mail : std::string
*/
std::string Utilisateur::getMail(){
    return this->mail;
}

/*
    * @brief Getter du mot de passe de l'utilisateur
    * @return mdp : std::string
*/
std::string Utilisateur::getPassword(){
    return this->mdp;
}

/*
    * @brief Getter des profils de l'utilisateur
    * @return profils : std::vector<Profil>
*/
std::vector<Profil> & Utilisateur::getProfils()
{
    return this->profils;
}

/*
    * @brief Getter des permissions de l'utilisateur
    * @return permissions : std::vector<bool>
*/
std::vector<bool> Utilisateur::getPermissions()
{
    return this->permissions;
}

/*
    * @brief Vérifie si l'utilisateur a les droits pour effectuer une action
    * @param droit : int
    * @return bool
*/
bool Utilisateur::can(int droit)
{
    return this->permissions.at(droit) == true;
}

/*
    * @brief Setter du nom de l'utilisateur
    * @param nom : nom de l'utilisateur
*/
void Utilisateur::setNom(std::string nom)
{
    this->nom = nom;
}

/*
    * @brief Setter du prénom de l'utilisateur
    * @param prenom : prénom de l'utilisateur
*/
void Utilisateur::setPrenom(std::string prenom)
{
    this->prenom = prenom;
}

/*
    * @brief Setter du mail de l'utilisateur
    * @param mail : mail de l'utilisateur
*/
void Utilisateur::setMail(std::string mail)
{
    this->mail = mail;
}

/*
    * @brief Setter du mot de passe de l'utilisateur
    * @param mdp : mot de passe de l'utilisateur
*/
void Utilisateur::setPassword(std::string mdp)
{
    this->mdp = mdp;
}

/*
    * @brief Ajoute un profil à l'utilisateur
    * @param profil : profil à ajouter
    * @return bool : true si l'ajout a été effectué, false sinon
*/
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

/*
    * @brief Supprime un profil à l'utilisateur
    * @param profil : profil à supprimer
    * @return bool : true si la suppression a été effectué, false sinon
*/
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

/*
    * @brief Supprime un profil à l'utilisateur
    * @param nomProfil : QString&
    * @return bool : true si la suppression a été effectué, false sinon
*/
bool Utilisateur::removeProfil(QString& nomProfil)
{
    for (auto p_iterator = profils.begin(); p_iterator != profils.end(); p_iterator++){
        if (nomProfil.compare(QString::fromStdString(p_iterator->getNomProfil())) == 0){
            profils.erase(p_iterator);
            return true;
        }
    }
    return false;
}

/*
    * @brief Ajoute une permission à l'utilisateur
    * @param permission : permission à ajouter
    * @return bool : true si l'ajout a été effectué, false sinon
*/
bool Utilisateur::addPermission(int permission)
{
    if (!this->can(permission))
    {
        this->permissions.at(permission) = true;
        return true;
    }
    return false;
}

/*
    * @brief Supprime une permission à l'utilisateur
    * @param permission : permission à supprimer
    * @return bool : true si la suppression a été effectué, false sinon
*/
bool Utilisateur::removePermission(int permission)
{
    if (this->can(permission))
    {
        this->permissions.at(permission) = false;
        return true;
    }
    return false;
}

/*
    * @brief Surcharge de l'opérateur ==
    * @param other : Utilisateur à comparer
    * @return bool : true si les deux utilisateurs sont identiques, false sinon
*/
bool Utilisateur::operator==(Utilisateur other)
{
    if (this->getMail() != other.getMail())
    {
        return false;
    }
    return true;
}
