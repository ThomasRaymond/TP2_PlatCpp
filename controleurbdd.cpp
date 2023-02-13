#include "controleurbdd.h"


int ControleurBDD::connexionUtilisateur(std::vector<QString>* credentials){
    // TODO

    delete(credentials);

    return 0;
}
void ControleurBDD::inscriptionUtilisateur(std::vector<QString>* credentials){
    // TODO

    delete(credentials);
    // Connexion.show (return true et c'est l'autre controleur qui affiche connexion)
    return;
}
int ControleurBDD::nombreUtilisateurs(){
    return 1;
}

