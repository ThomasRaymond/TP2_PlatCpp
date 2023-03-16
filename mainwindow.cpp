#include "mainwindow.h"
#include "controleurxml.h"
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
    fenetreChoixProfil = new ChoixProfil(this);

}

MainWindow::~MainWindow()
{
    delete ui;
    delete(utilisateur);
    delete(fenetreConnexion);
    delete(fenetreInscription);
    delete(fenetreVisualisationBDD);
    delete(fenetreChoixProfil);
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

Profil MainWindow::getProfilByName(QString nomProfil){

    std::vector<Profil> listeProfils = this->utilisateur->getProfils();

    for (auto it = listeProfils.begin(); it != listeProfils.end(); it++){
        if(QString::fromStdString(it->getNomProfil()) == nomProfil){
            return *it;
        }
    }
    return Profil("");
}

void MainWindow::setUtilisateur(Utilisateur* utilisateur){
    this->utilisateur=utilisateur;
}

void MainWindow::init(){
    switch (ControleurXML::nombreUtilisateurs())
    {
        // fichier vide
        case 0:
        {
            // On ajoute l'admin
            Utilisateur admin("admin","admin","admin@admin.admin","admin");
            admin.addPermission(READ);
            admin.addPermission(WRITE);
            admin.addPermission(DELETE);
            admin.addProfil(Profil("Profil_1"));
            admin.addProfil(Profil("Profil_2"));
            ControleurXML::addUser(admin);

            lancerInscription();
            break;
        }

        // 1 seul utilisateur dans l'XML (l'admin), on affiche l'inscription
        case 1:
        {
            lancerInscription();
            break;
        }

        // >= 2, on affiche la connexion
        default:
        {
            lancerConnexion();
            break;
        }
    }
}

void MainWindow::lancerConnexion()
{
    this->fenetreConnexion->clearfields();
    this->fenetreConnexion->show();
}

void MainWindow::lancerInscription()
{
    this->fenetreInscription->clearfields();
    this->fenetreInscription->show();
}

void MainWindow::lancerApplication(QString nomProfil)
{
    Profil profil;

    this->getProfilByName(nomProfil);

    fenetreVisualisationBDD->attachProfile(&profil);
    fenetreVisualisationBDD->init();

    this->fenetreVisualisationBDD->show();
}

void MainWindow::lancerChoixProfil(Utilisateur* utilisateur , int contexte){
    if (utilisateur != nullptr) setUtilisateur(utilisateur);
    this->fenetreChoixProfil->setContexte(contexte);
    this->fenetreChoixProfil->clearfields();
    this->fenetreChoixProfil->addListProfiles(this->utilisateur->getProfils());
    this->fenetreChoixProfil->show();
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
