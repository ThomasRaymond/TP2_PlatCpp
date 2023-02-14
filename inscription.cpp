#include "inscription.h"
#include "ui_inscription.h"
#include "connexion.h"
#include <iostream>

Inscription::Inscription(QWidget *parent)
    : QWidget(parent)
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
    Connexion c(this);
    c.show();
    return;
}

void Inscription::clickBoutonValider(){

    QString name = ui->inputNom->toPlainText();
    QString surname = ui->inputPrenom->toPlainText();
    QString mail = ui->inputMail->toPlainText();
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

    fields->push_back(name);
    fields->push_back(surname);
    fields->push_back(mail);
    fields->push_back(pswd);

    ControleurBDD controleurBDD;
    bool success = controleurBDD.inscriptionUtilisateur(fields);

    if (!success) {
        QMessageBox::warning(0, "Avertissement", "Cet utilisateur existe sûrement déjà !");
        return;
    }

    this->close();
    //Connexion
    return;
}
