#ifndef VISUALISATIONBDD_H
#define VISUALISATIONBDD_H

#include <QWidget>
#include <QMenu>
#include <QFileDialog>
#include <QMessageBox>
#include <filesystem>

#include "QtWidgets/qtreewidget.h"
#include "profil.h"
#include "bddtreeitem.h"

namespace Ui {
class VisualisationBDD;
}

// Classe permettant de gérer la fenêtre de visualisation de la base de données, de l'arborescence et de l'execution de requêtes
class VisualisationBDD : public QDialog
{
    Q_OBJECT

public:
    explicit VisualisationBDD(QWidget *parent = nullptr);
    ~VisualisationBDD();

    void attachProfile(Profil* profil);
    static int fenetreConfirmation(QString titre, QString description);
    void init();

private slots:
    void clickSelectionFichier();
    void clickEffacer();
    void clickExecuter();
    void clickDeconnexion();
    void clickChoixProfil();
    void clickTableArborescence(QTreeWidgetItem* item,int column);
    void rightClickOnTreeItem(QPoint idx);
    void removeCurrentItemFromTree();

private:
    Ui::VisualisationBDD *ui;
    Profil* profil;
    QSqlDatabase* currentDatabase;
    QMenu* contextMenu;
    QAction* delAction;

    int checkRightToExecute(QString requete);
    void CreateTree(Profil* profil);
    void UpdateTree(QSqlDatabase* db);
    void setDatabase(BDDTreeItem* dbItem);
};

#endif // VISUALISATIONBDD_H
