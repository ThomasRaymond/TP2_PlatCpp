#include "controleurbdd.h"


bool ControleurBDD::connexionUtilisateur(std::vector<QString>* credentials){
    // TODO

    delete(credentials);

    return true;
}
bool ControleurBDD::inscriptionUtilisateur(std::vector<QString>* credentials){
    // TODO

    delete(credentials);
    // Connexion.show (return true et c'est l'autre controleur qui affiche connexion)
    return true;
}
int ControleurBDD::nombreUtilisateurs(){
    return 1;
}

