#include "visualisationbdd.h"
#include "ui_visualisationbdd.h"

VisualisationBDD::VisualisationBDD(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::VisualisationBDD)
{
    profil = nullptr;
    currentDatabase = nullptr;

    ui->setupUi(this);
    ui->inputPath->setReadOnly(true);
    ui->vueTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    connect(ui->boutonSelection, SIGNAL(clicked()), SLOT(clickSelectionFichier()));
    connect(ui->boutonEffacer, SIGNAL(clicked()), SLOT(clickEffacer()));
    connect(ui->boutonExec, SIGNAL(clicked()), SLOT(clickExecuter()));
    connect(ui->boutonDeconnexion, SIGNAL(clicked()), SLOT(clickDeconnexion()));
}

VisualisationBDD::~VisualisationBDD()
{
    delete ui;
    profil = nullptr;
}

void VisualisationBDD::attachProfile(Profil* profil){
    this->profil = profil;
}

void VisualisationBDD::clickSelectionFichier(){
    QString cwd = QString::fromStdString(std::filesystem::current_path().string());
    QString chemin = QFileDialog::getOpenFileName(this, tr("Sélection d'une base de données"), cwd, tr("Fichiers de bases de données (*.sqlite)"));

    if (chemin != ""){
        QSqlDatabase* db_ptr = profil->getDbByName(chemin);

        if (db_ptr != nullptr){
            ui->inputPath->setText(chemin);
            currentDatabase = db_ptr;
        }
        else{
            QMessageBox::warning(0, "Erreur d'accès", "Votre profil n'est pas autorisé à accéder à cette base");
        }

    }

}

void VisualisationBDD::clickEffacer(){
    ui->inputSQL->clear();
}

void VisualisationBDD::clickExecuter(){
    QString commande = ui->inputSQL->text();

    if (currentDatabase != nullptr){
        QSqlQuery retourRequete = currentDatabase->exec(commande);

        if (retourRequete.size() == 0){
            ui->vueTable->clear();
            QMessageBox::information(0, "Information", "Le jeu de données retourné est vide.");
        }
        else{
            // TODO: Assigner la TableView
        }
    }
    else{
        QMessageBox::warning(0, "Erreur d'accès", "Veuillez connecter une base de données");
    }
}

void VisualisationBDD::clickDeconnexion(){
    QMessageBox confirmation;
    confirmation.setText("Vous allez être déconnecté.");
    confirmation.setInformativeText("Êtes-vous sûr de vouloir procéder à la déconnexion ?");
    confirmation.setStandardButtons(QMessageBox::Yes | QMessageBox::Cancel);
    confirmation.setDefaultButton(QMessageBox::Cancel);

    int reponse = confirmation.exec();

    if (reponse == QMessageBox::Yes){
        // TODO
    }
    else{
        return;
    }
}
