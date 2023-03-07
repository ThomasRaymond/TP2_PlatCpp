#include "choixprofil.h"
#include "ui_choixprofil.h"
#include "mainwindow.h"

ChoixProfil::ChoixProfil(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChoixProfil)
{
    ui->setupUi(this);
    connect(ui->boutonValider, SIGNAL(clicked()), SLOT(clickValider()));
    connect(ui->boutonAnnuler, SIGNAL(clicked()), SLOT(clickAnnuler()));
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

void ChoixProfil::clearfields(){
    ui->inputProfil->clear();
}

void ChoixProfil::clickValider(){
    QString profilSelectionne = ui->inputProfil->currentText();
    if(!profilSelectionne.isEmpty()){
        this->hide();
        static_cast<MainWindow*>(this->parent())->lancerApplication(profilSelectionne);
    }
    else{
        QMessageBox::warning(0, "Erreur dans le choix du profil", "Veuillez choisir un profil valide");
    }
}

void ChoixProfil::clickAnnuler(){
    this->hide();
    static_cast<MainWindow*>(this->parent())->deconnexion();
}
