#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "utilisateur.h"
#include "connexion.h"
#include "inscription.h"
#include "visualisationbdd.h"

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

    void setUtilisateur(Utilisateur* utilisateur);

    void init();
    void lancerApplication(Utilisateur* utilisateur);
    void lancerConnexion();
    void lancerInscription();
    void deconnexion();

    void fermerFenetre(QDialog* fenetre);

private:
    Ui::MainWindow *ui;
    Utilisateur* utilisateur;

    // Fenêtres
    Connexion* fenetreConnexion;
    Inscription* fenetreInscription;
    VisualisationBDD* fenetreVisualisationBDD;
};
#endif // MAINWINDOW_H
