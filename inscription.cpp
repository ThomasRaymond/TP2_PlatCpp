
#include "inscription.h"
#include "ui_inscription.h"

Inscription::Inscription(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Inscription)
{
    ui->setupUi(this);
    connect(ui->boutonValider, SIGNAL(clicked()), SLOT(on_boutonValider_clicked()));
    connect(ui->boutonAnnuler, SIGNAL(clicked()), SLOT(on_boutonAnnuler_clicked()));
}

Inscription::~Inscription()
{
    delete ui;
}

void Inscription::on_boutonAnnuler_clicked(){

}

std::vector<QString>* Inscription::on_boutonValider_clicked(){

    QString name = ui->inputNom->toPlainText();
    QString surname = ui->inputPrenom->toPlainText();
    QString mail = ui->inputMail->toPlainText();
    QString pswd = ui->inputMDP->text();
    QString confPswd = ui->inputConfirmationMDP->text();

    if (pswd == confPswd) {
        std::vector<QString>* fields = new std::vector<QString>(4);

        fields->push_back(name);
        fields->push_back(surname);
        fields->push_back(mail);
        fields->push_back(pswd);

        return fields;
    }
    else {
        return nullptr;
    }
}
