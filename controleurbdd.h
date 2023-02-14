#ifndef CONTROLEURBDD_H
#define CONTROLEURBDD_H

#include <QtSql/QSql>
#include <vector>
#include <qstring.h>



class ControleurBDD {
public :
    bool connexionUtilisateur(std::vector<QString>* credentials);
    bool inscriptionUtilisateur(std::vector<QString>* credentials);
    int nombreUtilisateurs();
};

#endif // CONTROLEURBDD_H
