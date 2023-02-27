#include "mainwindow.h"
#include "inscription.h"
#include "controleurbdd.h"
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
    ControleurBDD cBDD;
    if (cBDD.nombreUtilisateurs()>1){
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

void MainWindow::validerConnexion(std::vector<QString>* credentials, QDialog* fenetre){

    ControleurBDD controleurBDD;
    bool utilisateurExiste = controleurBDD.connexionUtilisateur(credentials);

    if (!utilisateurExiste) {
        QMessageBox::warning(0, "Avertissement", "Cet utilisateur n'existe pas !");
        return;
    }
    fermerFenetre(fenetre);
    lancerApplication();

}

void MainWindow::validerInscription(std::vector<QString>* credentials, QDialog* fenetre){

    ControleurBDD controleurBDD;
    bool success = controleurBDD.inscriptionUtilisateur(credentials);

    if (!success) {
        QMessageBox::warning(0, "Avertissement", "Cet utilisateur existe sûrement déjà !");
        return;
    }

    fermerFenetre(fenetre);
    lancerConnexion();


}

void MainWindow::fermerFenetre(QDialog* fenetre){
    fenetre->close();
}
