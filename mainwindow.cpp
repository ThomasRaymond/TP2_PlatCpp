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
}

MainWindow::~MainWindow()
{
    delete ui;
}

Utilisateur* MainWindow::getUtilisateur(){
    return this->utilisateur;
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
    QDialog* conn = new Connexion(this);
    conn->exec();
}

void MainWindow::lancerInscription()
{
    QDialog* inscription = new Inscription(this);
    inscription->exec();
}

void MainWindow::lancerApplication()
{
    QMessageBox::warning(0, "Avertissement", "Vous êtes connecté !");
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
