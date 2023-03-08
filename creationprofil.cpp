#include "creationprofil.h"
#include "choixprofil.h"
#include "ui_creationprofil.h"

CreationProfil::CreationProfil(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CreationProfil)
{
    ui->setupUi(this);
    connect(ui->BoutonAnnuler, SIGNAL(clicked()), SLOT(clickAnnuler()));
    connect(ui->boutonEnregistrer, SIGNAL(clicked()), SLOT(clickValider()));
}

CreationProfil::~CreationProfil()
{
    delete ui;
}

void CreationProfil::clickAnnuler(){
    this->close();
}

void CreationProfil::clickValider(){
    this->hide();
    QString nom = ui->inputNomProfil->text();
    static_cast<ChoixProfil*>(this->parent())->enregistrerProfil(nom);
}
