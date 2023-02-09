#ifndef CONTROLEURBDD_H
#define CONTROLEURBDD_H

#include <QtSql/QSql>

namespace controleurBDD {
    int connexionUtilisateur(std::vector<QString>* credentials);
    void inscriptionUtilisateur(std::vector<QString>* credentials);

}

#endif // CONTROLEURBDD_H
