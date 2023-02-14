#include "connexion.h"
#include "ui_connexion.h"
#include <iostream>

Connexion::Connexion(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Connexion)
{
    ui->setupUi(this);
    connect(ui->boutonValider, SIGNAL(clicked()), SLOT(clickBoutonValider()));
    connect(ui->boutonInscription, SIGNAL(clicked()), SLOT(clickBoutonInscription()));
}

Connexion::~Connexion()
{
    delete ui;
}

void Connexion::clickBoutonInscription()
{
    this->close();
    Inscription i(this);
    i.show();
}

void Connexion::clickBoutonValider()
{

    QString mail = ui->inputMail->toPlainText();
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

    std::vector<QString>* fields = new std::vector<QString>(2);

    fields->push_back(mail);
    fields->push_back(pswd);

    ControleurBDD controleurBDD;
    bool utilisateurExiste = controleurBDD.connexionUtilisateur(fields);

    if (!utilisateurExiste) {
        QMessageBox::warning(0, "Avertissement", "Cet utilisateur n'existe pas !");
        return;
    }

    this->close();
    //Connexion

    return;
}
