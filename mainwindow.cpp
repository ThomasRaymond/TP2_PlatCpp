#include "mainwindow.h"
#include "inscription.h"
#include "controleurxml.h"
#include "connexion.h"
#include "ui_mainwindow.h"

#include "connexion.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    utilisateur = nullptr;

    fenetreConnexion = new Connexion(this);
    fenetreInscription = new Inscription(this);
    fenetreVisualisationBDD = new VisualisationBDD(this);

}

MainWindow::~MainWindow()
{
    delete ui;
    delete(utilisateur);
    delete(fenetreConnexion);
    delete(fenetreInscription);
    delete(fenetreVisualisationBDD);
}

Utilisateur* MainWindow::getUtilisateur(){
    return this->utilisateur;
}

Connexion* MainWindow::getFenetreConnexion(){
    return this->fenetreConnexion;
}
Inscription* MainWindow::getFenetreInscription(){
    return this->fenetreInscription;
}
VisualisationBDD* MainWindow::getFenetreVisualisationBDD(){
    return this->fenetreVisualisationBDD;
}

void MainWindow::setUtilisateur(Utilisateur* utilisateur){
    this->utilisateur=utilisateur;
}

void MainWindow::init(){
    if (ControleurXML::nombreUtilisateurs() > 1)
    {
        lancerConnexion();
    }
    else
    {
        lancerInscription();
    }
}

void MainWindow::lancerConnexion()
{
    this->fenetreConnexion->exec();
}

void MainWindow::lancerInscription()
{
    this->fenetreInscription->exec();
}

void MainWindow::lancerApplication(Utilisateur* utilisateur)
{
    setUtilisateur(utilisateur);

    // Choix profil


    this->fenetreVisualisationBDD->show();
}

void MainWindow::deconnexion(){
    delete(this->utilisateur);
    this->utilisateur = nullptr;
    lancerConnexion();
}

void MainWindow::fermerFenetre(QDialog* fenetre)
{
    fenetre->close();
}
