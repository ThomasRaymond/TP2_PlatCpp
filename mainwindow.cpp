#include "mainwindow.h"
#include "controleurxml.h"
#include "ui_mainwindow.h"

#include "connexion.h"

// Constructeur
/*
    * @brief Constructeur de la classe MainWindow
    * @param parent : QWidget parent
*/
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

// Destructeur
/*
    * @brief Destructeur de la classe MainWindow
*/
MainWindow::~MainWindow()
{
    delete ui;
    delete(utilisateur);
    delete(fenetreConnexion);
    delete(fenetreInscription);
    delete(fenetreVisualisationBDD);
    delete(fenetreChoixProfil);
}

/*
    * @brief Getter de l'utilisateur
    * @return utilisateur : Utilisateur*
*/
Utilisateur* MainWindow::getUtilisateur(){
    return this->utilisateur;
}

/*
    * @brief Getter de la fenêtre de connexion
    * @return fenetreConnexion : Connexion*
*/
Connexion* MainWindow::getFenetreConnexion(){
    return this->fenetreConnexion;
}

/*
    * @brief Getter de la fenêtre d'inscription
    * @return fenetreInscription : Inscription*
*/
Inscription* MainWindow::getFenetreInscription(){
    return this->fenetreInscription;
}

/*
    * @brief Getter de la fenêtre de visualisation de la BDD
    * @return fenetreVisualisationBDD : VisualisationBDD*
*/
VisualisationBDD* MainWindow::getFenetreVisualisationBDD(){
    return this->fenetreVisualisationBDD;
}

/*
    * @brief Setter de l'utilisateur connecté
    * @param utilisateur : Utilisateur*
*/
void MainWindow::setUtilisateur(Utilisateur* utilisateur){
    this->utilisateur=utilisateur;
}

/*
    * @brief Fonction d'initialisation de la fenêtre principale
*/
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

/*
    * @brief Méthode lancant la fenêtre de connexion
*/
void MainWindow::lancerConnexion()
{
    this->fenetreConnexion->clearfields();
    this->fenetreConnexion->show();
}

/*
    * @brief Méthode lancant la fenêtre d'inscription
*/
void MainWindow::lancerInscription()
{
    this->fenetreInscription->clearfields();
    this->fenetreInscription->show();
}

/*
    * @brief Méthode lancant la fenêtre de visualisation de la BDD
*/
void MainWindow::lancerApplication(int index)
{

    Profil& profil = getUtilisateur()->getProfils().at(index);

    fenetreVisualisationBDD->attachProfile(&profil);
    fenetreVisualisationBDD->init();

    this->fenetreVisualisationBDD->show();
}

/*
    * @brief Méthode lancant la fenêtre de choix de profil
*/
void MainWindow::lancerChoixProfil(Utilisateur* utilisateur , int contexte){
    if (utilisateur != nullptr) setUtilisateur(utilisateur);
    this->fenetreChoixProfil->setContexte(contexte);
    this->fenetreChoixProfil->clearfields();
    this->fenetreChoixProfil->addListProfiles(this->utilisateur->getProfils());
    this->fenetreChoixProfil->show();
}

/*
    * @brief Méthode de déconnexion
*/
void MainWindow::deconnexion(){
    this->utilisateur = nullptr;
    lancerConnexion();
}

/*
    * @brief Méthode de fermeture de la fenêtre
    * @param fenetre : QDialog*
*/
void MainWindow::fermerFenetre(QDialog* fenetre)
{
    fenetre->close();
}
