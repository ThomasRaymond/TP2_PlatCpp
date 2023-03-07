#include "connexion.h"
#include "ui_connexion.h"
#include "mainwindow.h"
#include "utilisateur.h"
#include "controleurxml.h"
#include <iostream>

Connexion::Connexion(QWidget *parent) :
    QDialog(parent),
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

void Connexion::clearfields(){
    ui->inputMail->clear();
    ui->inputMDP->clear();
}

void Connexion::clickBoutonInscription()
{
    this->hide();
    static_cast<MainWindow*>(this->parent())->lancerInscription();
}

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
        QMessageBox::information(0, "Succès", "Vous êtes connecté !");
        this->hide();
        static_cast<MainWindow*>(this->parent())->lancerChoixProfil(user);
    }
    else
    {
        QMessageBox::critical(0, "Erreur", "Connexion impossible !");
    }
}
