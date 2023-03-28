#include "profil.h"

// Constructeur
/*
    * @brief Constructeur de la classe Profil
*/
Profil::Profil()
{
    this->nomProfil = "";
    this->databases.clear();
}

/*
    * @brief Constructeur de la classe Profil à partir d'un nom de profil
    * @param nomProfil : nom du profil
*/
Profil::Profil(std::string nomProfil) {
    this->nomProfil = nomProfil;
}

/*
    * @brief Getter du nom du profil
    * @return nomProfil : std::string
*/
const std::string Profil::getNomProfil() {
    return this->nomProfil;
}

/*
    * @brief Setter du nom du profil
    * @param nomProfil : nom du profil
*/
void Profil::setNomProfil(std::string nomProfil){
    this->nomProfil = nomProfil;
}

/*
    * @brief Surcharge de l'opérateur ==
    * @param other : Profil à comparer
    * @return bool : true si les profils sont égaux, false sinon
*/
bool Profil::operator==(const Profil &other) const {
    return this->nomProfil == other.nomProfil;
}
