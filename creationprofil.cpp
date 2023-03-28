#include "creationprofil.h"
#include "choixprofil.h"
#include "ui_creationprofil.h"

// Constructeur
/*
    * @brief Constructeur de la classe CreationProfil
    * @param parent : QWidget parent
*/
CreationProfil::CreationProfil(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CreationProfil)
{
    ui->setupUi(this);
    connect(ui->BoutonAnnuler, SIGNAL(clicked()), SLOT(clickAnnuler()));
    connect(ui->boutonEnregistrer, SIGNAL(clicked()), SLOT(clickValider()));
}

// Destructeur
/*
    * @brief Destructeur de la classe CreationProfil
*/
CreationProfil::~CreationProfil()
{
    delete ui;
}

/*
    * @brief Slot appelé lors du clic sur le bouton Annuler
*/
void CreationProfil::clickAnnuler(){
    this->close();
}

/*
    * @brief Slot appelé lors du clic sur le bouton Valider
*/
void CreationProfil::clickValider(){
    this->hide();
    QString nom = ui->inputNomProfil->text();

    if (nom == "")
    {
        QMessageBox::warning(0, "Attention", "Vous pouvez pas entrer un nom de profil vide !");
        return;
    }

    static_cast<ChoixProfil*>(this->parent())->enregistrerProfil(nom);
}
