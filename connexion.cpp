#include "connexion.h"
#include "ui_connexion.h"
#include "mainwindow.h"
#include "utilisateur.h"
#include "controleurxml.h"
#include <iostream>

// Constructeur
/*
    * @brief Constructeur de la classe Connexion
    * @param parent : QWidget parent
*/
Connexion::Connexion(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Connexion)
{
    ui->setupUi(this);
    connect(ui->boutonValider, SIGNAL(clicked()), SLOT(clickBoutonValider()));
    connect(ui->boutonInscription, SIGNAL(clicked()), SLOT(clickBoutonInscription()));
}

// Destructeur
/*
    * @brief Destructeur de la classe Connexion
*/
Connexion::~Connexion()
{
    delete ui;
}

/*
    * @brief Vide les champs de la fenêtre
*/
void Connexion::clearfields(){
    ui->inputMail->clear();
    ui->inputMDP->clear();
}

/*
    * @brief Slot appelé lors du clic sur le bouton d'inscription
*/
void Connexion::clickBoutonInscription()
{
    this->hide();
    static_cast<MainWindow*>(this->parent())->lancerInscription();
}

/*
    * @brief Slot appelé lors du clic sur le bouton Valider
*/
void Connexion::clickBoutonValider()
{
    QString mail = ui->inputMail->text();
    QString pswd = ui->inputMDP->text();

    static QRegularExpression mailRegex("[\\w]+[@]{1}[\\w]+([.][\\w]{2,})+");

    /* --- Vérifications --- */

    if (mail.isEmpty() || pswd.isEmpty()){
        QMessageBox::warning(0, "Avertissement", "Veuillez renseigner tous les champs");
        return;
    }
    else if (!mailRegex.match(mail).hasMatch()) {
        QMessageBox::critical(0, "Erreur", "Veuillez renseigner un bon format d'adresse mail");
        return;
    }

    /* --- Connexion --- */


    Utilisateur* user = ControleurXML::verifyUser(mail.toStdString(), pswd.toStdString());

    if (user != nullptr)
    {
        this->hide();
        static_cast<MainWindow*>(this->parent())->lancerChoixProfil(user, CONTEXT_FIRST_ACCESS);
    }
    else
    {
        QMessageBox::critical(0, "Erreur", "Connexion impossible !");
    }
}
