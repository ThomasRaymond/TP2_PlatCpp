#ifndef CONTROLEURBDD_H
#define CONTROLEURBDD_H

#include <QtSql/QSql>
#include <vector>
#include <qstring.h>



class ControleurBDD {
public :
    int connexionUtilisateur(std::vector<QString>* credentials);
    void inscriptionUtilisateur(std::vector<QString>* credentials);
    int nombreUtilisateurs();
};

#endif // CONTROLEURBDD_H
