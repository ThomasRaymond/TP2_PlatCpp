#ifndef VISUALISATIONBDD_H
#define VISUALISATIONBDD_H

#include <QWidget>
#include <QFileDialog>
#include <QMessageBox>
#include <filesystem>

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

private slots:
    void clickSelectionFichier();
    void clickEffacer();
    void clickExecuter();
    void clickDeconnexion();

private:
    Ui::VisualisationBDD *ui;
    Profil* profil;
    QSqlDatabase* currentDatabase;

    bool checkRightToExecute(QString requete);
};

#endif // VISUALISATIONBDD_H
