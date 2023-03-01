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
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::init(){
    // TO DO : CHECK NOMBRE D'UTILISATEURS
    if (ControleurXML::nombreUtilisateurs() > 1){
        lancerConnexion();
    }
    else {
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

void MainWindow::lancerApplication(){
    QMessageBox::warning(0, "Avertissement", "Vous êtes connecté !");
}

void MainWindow::fermerFenetre(QDialog* fenetre){
    fenetre->close();
}
