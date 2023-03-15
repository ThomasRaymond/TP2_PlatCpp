#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "utilisateur.h"
#include "connexion.h"
#include "inscription.h"
#include "visualisationbdd.h"
#include "choixprofil.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    Utilisateur* getUtilisateur();
    Connexion* getFenetreConnexion();
    Inscription* getFenetreInscription();
    VisualisationBDD* getFenetreVisualisationBDD();
    ChoixProfil* getFenetreChoixProfil();
    Profil getProfilByName(QString nomProfil);

    void setUtilisateur(Utilisateur* utilisateur);

    void init();
    void lancerApplication(QString nomProfil);
    void lancerConnexion();
    void lancerInscription();
    void lancerChoixProfil(Utilisateur* utilisateur, int contexte);
    void deconnexion();

    void fermerFenetre(QDialog* fenetre);

private:
    Ui::MainWindow *ui;
    Utilisateur* utilisateur;

    // Fenêtres
    Connexion* fenetreConnexion;
    Inscription* fenetreInscription;
    VisualisationBDD* fenetreVisualisationBDD;
    ChoixProfil* fenetreChoixProfil;
};
#endif // MAINWINDOW_H
