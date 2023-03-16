#include "choixprofil.h"
#include "ui_choixprofil.h"
#include "creationprofil.h"
#include "mainwindow.h"

ChoixProfil::ChoixProfil(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChoixProfil)
{
    ui->setupUi(this);
    connect(ui->boutonValider, SIGNAL(clicked()), SLOT(clickValider()));
    connect(ui->boutonAnnuler, SIGNAL(clicked()), SLOT(clickAnnuler()));
    connect(ui->boutonNvProfil, SIGNAL(clicked()), SLOT(creerProfil()));
}

ChoixProfil::~ChoixProfil()
{
    delete ui;
}

void ChoixProfil::addListProfiles(std::vector<Profil> list){
    for (auto it = list.begin(); it != list.end(); it++){
        ui->inputProfil->addItem(QString::fromStdString(it->getNomProfil()));
    }
}

void ChoixProfil::clearfields()
{
    ui->inputProfil->clear();
}

int ChoixProfil::getContexte(){
    return this->contexte;
}

void ChoixProfil::setContexte(int contexte){
    this->contexte = contexte;
}

void ChoixProfil::clickValider()
{
    QString profilSelectionne = ui->inputProfil->currentText();
    int indexComboBox = ui->inputProfil->currentIndex();
    if(!profilSelectionne.isEmpty()){
        this->hide();
        static_cast<MainWindow*>(this->parent())->lancerApplication(indexComboBox);
    }
    else{
        QMessageBox::warning(0, "Erreur dans le choix du profil", "Veuillez choisir un profil valide");
    }
}

void ChoixProfil::clickAnnuler()
{
    this->hide();
    if(getContexte() == CONTEXT_FIRST_ACCESS){
        static_cast<MainWindow*>(this->parent())->deconnexion();
    }
    else if(getContexte() == CONTEXT_CHANGE_PROFILE){
        return;
    }
}

void ChoixProfil::creerProfil()
{
    CreationProfil fenetreCreationProfil(this);
    fenetreCreationProfil.exec();

}

void ChoixProfil::enregistrerProfil(QString nomProfil)
{
    static_cast<MainWindow*>(this->parent())->getUtilisateur()->addProfil(Profil(nomProfil.toStdString()));
    ui->inputProfil->addItem(nomProfil);
}
