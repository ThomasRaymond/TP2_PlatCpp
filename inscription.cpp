#include "inscription.h"

#include "ui_inscription.h"
#include "mainwindow.h"
#include "utilisateur.h"
#include "controleurxml.h"

Inscription::Inscription(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Inscription)
{
    ui->setupUi(this);
    connect(ui->boutonValider, SIGNAL(clicked()), SLOT(clickBoutonValider()));
    connect(ui->boutonConnexion, SIGNAL(clicked()), SLOT(clickBoutonConnexion()));
}

Inscription::~Inscription()
{
    delete ui;
}

void Inscription::clickBoutonConnexion()
{
    this->hide();
    static_cast<MainWindow*>(this->parent())->lancerConnexion();
    return;
}

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
