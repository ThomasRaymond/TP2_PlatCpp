#include "inscription.h"
#include "ui_inscription.h"
#include "connexion.h"
#include "mainwindow.h"
#include "utilisateur.h"
#include "controleurxml.h"
#include <iostream>

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
    Connexion c(this);
    c.exec();
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

    // Récupèration des utilisateurs existants
    std::vector<Utilisateur> users = ControleurXML::parseFile();

    // Ajout du nouvel utilisateur aux utilisateurs existants
    users.push_back(user);

    // Ecriture du fichier
    ControleurXML::writeFile(users);

    return;
}
