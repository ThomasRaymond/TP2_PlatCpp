#include "inscription.h"

#include "ui_inscription.h"
#include "mainwindow.h"
#include "utilisateur.h"
#include "controleurxml.h"

// Constructeur
/*
    * @brief Constructeur de la classe Inscription
    * @param parent : QWidget parent
*/
Inscription::Inscription(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Inscription)
{
    ui->setupUi(this);
    connect(ui->boutonValider, SIGNAL(clicked()), SLOT(clickBoutonValider()));
    connect(ui->boutonConnexion, SIGNAL(clicked()), SLOT(clickBoutonConnexion()));
}

// Destructeur
/*
    * @brief Destructeur de la classe Inscription
*/
Inscription::~Inscription()
{
    delete ui;
}

/*
    * @brief Vide les champs de la fenêtre
*/
void Inscription::clearfields(){
    ui->inputNom->clear();
    ui->inputPrenom->clear();
    ui->inputMail->clear();
    ui->inputMDP->clear();
    ui->inputConfirmationMDP->clear();
}

/*
    * @brief Slot appelé lors du clic sur le bouton de connexion
*/
void Inscription::clickBoutonConnexion()
{
    this->hide();
    static_cast<MainWindow*>(this->parent())->lancerConnexion();
    return;
}

/*
    * @brief Slot appelé lors du clic sur le bouton Valider
*/
void Inscription::clickBoutonValider(){

    QString name = ui->inputNom->text();
    QString surname = ui->inputPrenom->text();
    QString mail = ui->inputMail->text();
    QString pswd = ui->inputMDP->text();
    QString confPswd = ui->inputConfirmationMDP->text();

    static QRegularExpression mailRegex("[\\w]+[@]{1}[\\w]+([.][\\w]{2,})+");

    /* --- Vérifications --- */

    if (name.isEmpty() || surname.isEmpty() || mail.isEmpty() || pswd.isEmpty() || confPswd.isEmpty()){
        QMessageBox::warning(0, "Avertissement", "Veuillez renseigner tous les champs");
        return;
    }
    else if (!mailRegex.match(mail).hasMatch()) {
        QMessageBox::critical(0, "Erreur", "Veuillez renseigner un bon format d'adresse mail");
        return;
    }
    else if (pswd != confPswd) {
        QMessageBox::critical(0, "Erreur", "Les mots de passe ne correspondent pas");
        return;
    }

    /* --- Creation d'un utilisateur --- */

    Utilisateur user;

    user.setPrenom(surname.toStdString());
    user.setNom(name.toStdString());
    user.setMail(mail.toStdString());
    user.setPassword(pswd.toStdString());

    /* --- Ajout de l'utilisateur dans le fichier XML --- */
    if (ControleurXML::addUser(user))
    {
        QMessageBox::information(0, "Succès", "L'utilisateur a bien été ajouté");
    }
    else
    {
        QMessageBox::critical(0, "Erreur", "Ajout impossible");
    }

    return;
}
