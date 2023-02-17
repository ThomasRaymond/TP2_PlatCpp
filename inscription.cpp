#include "inscription.h"
#include "ui_inscription.h"
#include "connexion.h"
#include "mainwindow.h"
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

    /* --- Ajout de l'utilisateur dans la BDD --- */

    std::vector<QString>* fields = new std::vector<QString>(4);


    fields->insert(fields->begin(), name);
    fields->insert(fields->begin() + 1, surname);
    fields->insert(fields->begin() + 2, mail);
    fields->insert(fields->begin() + 3, pswd);
    static_cast<MainWindow*>(this->parent())->validerInscription(fields, this);

    return;
}
