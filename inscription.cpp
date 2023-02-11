
#include "inscription.h"
#include "ui_inscription.h"

Inscription::Inscription(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Inscription)
{
    ui->setupUi(this);
    connect(ui->boutonValider, SIGNAL(clicked()), SLOT(clickBoutonValider()));
    connect(ui->boutonAnnuler, SIGNAL(clicked()), SLOT(clickBoutonAnnuler()));
}

Inscription::~Inscription()
{
    delete ui;
}

void Inscription::clickBoutonAnnuler(){
    if (this->parent() == nullptr){
        QMessageBox::warning(0, "Avertissement", "Vous ne pouvez revenir en arrière");
    }
    else {
        this->close();
        QCoreApplication::quit();
    }
}

void Inscription::clickBoutonValider(){

    QString name = ui->inputNom->toPlainText();
    QString surname = ui->inputPrenom->toPlainText();
    QString mail = ui->inputMail->toPlainText();
    QString pswd = ui->inputMDP->text();
    QString confPswd = ui->inputConfirmationMDP->text();

    if (name.isEmpty() || surname.isEmpty() || mail.isEmpty() || pswd.isEmpty() || confPswd.isEmpty()){
        QMessageBox::warning(0, "Avertissement", "Veuillez renseigner tous les champs");
        return;
    }
    else if (!mail.contains('@')) {
        QMessageBox::critical(0, "Erreur", "Veuillez renseigner un bon format d'adresse mail");
        return;
    }
    else if (pswd == confPswd) {
        std::vector<QString>* fields = new std::vector<QString>(4);

        fields->push_back(name);
        fields->push_back(surname);
        fields->push_back(mail);
        fields->push_back(pswd);

        ControleurBDD::inscriptionUtilisateur(fields);

        this->close();
        //Connection.show
        return;
    }
    else {
        QMessageBox::critical(0, "Erreur", "Les mots de passe ne correspondent pas");
        return;
    }
}
