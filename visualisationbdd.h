#ifndef VISUALISATIONBDD_H
#define VISUALISATIONBDD_H

#include <QWidget>
#include <QMenu>
#include <QFileDialog>
#include <QMessageBox>
#include <filesystem>

#include "QtWidgets/qtreewidget.h"
#include "profil.h"

namespace Ui {
class VisualisationBDD;
}

class VisualisationBDD : public QDialog
{
    Q_OBJECT

public:
    explicit VisualisationBDD(QWidget *parent = nullptr);
    ~VisualisationBDD();

    void attachProfile(Profil* profil);
    int fenetreConfirmation(QString titre, QString description);
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

    bool checkRightToExecute(QString requete);
    void CreateTree(Profil* profil);
    void UpdateTree(QSqlDatabase* db);
};

#endif // VISUALISATIONBDD_H
