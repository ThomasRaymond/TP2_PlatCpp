#include "choixprofil.h"
#include "ui_choixprofil.h"
#include "creationprofil.h"
#include "mainwindow.h"

// Constructeur
/*
    * @brief Constructeur de la classe ChoixProfil
    * @param parent : QWidget parent
*/
ChoixProfil::ChoixProfil(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChoixProfil)
{
    ui->setupUi(this);
    connect(ui->boutonValider, SIGNAL(clicked()), SLOT(clickValider()));
    connect(ui->boutonAnnuler, SIGNAL(clicked()), SLOT(clickAnnuler()));
    connect(ui->boutonNvProfil, SIGNAL(clicked()), SLOT(creerProfil()));
}

// Destructeur
/*
    * @brief Destructeur de la classe ChoixProfil
*/
ChoixProfil::~ChoixProfil()
{
    delete ui;
}

/*
    * @brief Ajoute les profils de l'utilisateur à la liste déroulante
    * @param list : liste des profils de l'utilisateur
*/
void ChoixProfil::addListProfiles(std::vector<Profil> list){
    for (auto it = list.begin(); it != list.end(); it++){
        ui->inputProfil->addItem(QString::fromStdString(it->getNomProfil()));
    }
}

/*
    * @brief Vide les champs de la fenêtre
*/
void ChoixProfil::clearfields()
{
    ui->inputProfil->clear();
}

/*
    * @brief Retourne le contxte d'ouverture de la fenêtre
    * @return contexte : int
*/
int ChoixProfil::getContexte(){
    return this->contexte;
}

/*
    * @brief Modifie le contexte d'ouverture de la fenêtre
    * @param contexte : int
*/
void ChoixProfil::setContexte(int contexte){
    this->contexte = contexte;
}

/*
    * @brief Slot appelé lors du clic sur le bouton Valider
*/
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

/*
    * @brief Slot appelé lors du clic sur le bouton Annuler
*/
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

/*
    * @brief Slot appelé lors du clic sur le bouton Nouveau Profil
*/
void ChoixProfil::creerProfil()
{
    CreationProfil fenetreCreationProfil(this);
    fenetreCreationProfil.exec();

}

/*
    * @brief Ajoute le profil à la liste des profils de l'utilisateur
    * @param nomProfil : QString
*/
void ChoixProfil::enregistrerProfil(QString nomProfil)
{
    static_cast<MainWindow*>(this->parent())->getUtilisateur()->addProfil(Profil(nomProfil.toStdString()));
    ControleurXML::updateUser(*static_cast<MainWindow*>(this->parent())->getUtilisateur());
    ui->inputProfil->addItem(nomProfil);
}
