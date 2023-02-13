#include "connexion.h"
#include "ui_connexion.h"

Connexion::Connexion(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Connexion)
{
    ui->setupUi(this);
    //connect(ui->boutonValider, SIGNAL(clicked()), SLOT(clickBoutonValider()));
    connect(ui->boutonAnnuler, SIGNAL(clicked()), SLOT(clickBoutonAnnuler()));
}

Connexion::~Connexion()
{
    delete ui;
}

void Connexion::clickBoutonAnnuler(){
    if (this->parent() == nullptr){
        QMessageBox::warning(0, "Avertissement", "Vous ne pouvez revenir en arrière");
    }
    else {
        this->close();
        QCoreApplication::quit();
    }
}
