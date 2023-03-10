#include "mainwindow.h"
#include "ui_visualisationbdd.h"
#include "visualisationbdd.h"

VisualisationBDD::VisualisationBDD(QWidget *parent) :
    QDialog(parent),
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

void VisualisationBDD::attachProfile(Profil* profil)
{
    this->profil = profil;
}

int VisualisationBDD::fenetreConfirmation(QString titre, QString description){
    QMessageBox confirmation;
    confirmation.setText(titre);
    confirmation.setInformativeText(description);
    confirmation.setStandardButtons(QMessageBox::Yes | QMessageBox::Cancel);
    confirmation.button(QMessageBox::Yes)->setText("Oui");
    confirmation.button(QMessageBox::Cancel)->setText("Annuler");
    confirmation.setDefaultButton(QMessageBox::Cancel);

    int maxSize = std::max(titre.size(), description.size()) * 6;                           // C'est quoi ce bordel ?
    confirmation.setStyleSheet("QLabel{min-width:" + QString::number(maxSize) + ";  } ");   //           -

    return confirmation.exec();
}

void VisualisationBDD::clickSelectionFichier()
{
    QString cwd = QString::fromStdString(std::filesystem::current_path().string());

    // Generate a useless "+[CATransaction synchronize] called within transaction" warning on MacOS
    QString chemin = QFileDialog::getOpenFileName(this, tr("Sélection d'une base de données"), cwd, tr("Fichiers de bases de données (*.sqlite)"));

    QMessageBox::information(0, "Information", chemin);

    if (chemin != "")
    {
        profil->getDatabases().push_back(QSqlDatabase::addDatabase(chemin));
        // TODO handle errors

        Utilisateur current_user = *((MainWindow*)this->parent())->getUtilisateur();
        ControleurXML::updateUser(current_user,current_user);
    }
}

void VisualisationBDD::clickEffacer()
{
    ui->inputSQL->clear();
}

void VisualisationBDD::clickExecuter()
{
    QString commande = ui->inputSQL->text();

    if (currentDatabase != nullptr){
        QMessageBox::warning(0, "Erreur d'accès", "Veuillez connecter une base de données");
    }

    if(checkRightToExecute(commande))
    {
        QSqlQuery retourRequete = currentDatabase->exec(commande);

        if (retourRequete.size() == 0)
        {
            ui->vueTable->clearSpans();
            QMessageBox::information(0, "Information", "Le jeu de données retourné est vide :\n" + retourRequete.lastError().text(), QMessageBox::Ok, QMessageBox::Ok);

        }
        else{
            QMessageBox::information(0, "Information", "La requête a retourné " + QString::number(retourRequete.size()) + " résultat(s)");
            QSqlQueryModel modele;
            modele.setQuery(std::move(retourRequete));
            ui->vueTable->setModel(&modele);
        }
    }
    else
    {
        QMessageBox::critical(0, "Erreur d'exécution", "Vous n'avez pas les droits nécéssaires pour exécuter cette requête");
    }
}

void VisualisationBDD::clickDeconnexion()
{
    int reponse = fenetreConfirmation("Vous allez être déconnecté.", "Êtes-vous sûr de vouloir procéder à la déconnexion ?");

    if (reponse == QMessageBox::Yes){
        this->hide();
        static_cast<MainWindow*>(this->parent())->deconnexion();
    }
}

bool VisualisationBDD::checkRightToExecute(QString requete)
{
    if (requete.contains("ADD", Qt::CaseInsensitive) ||
            requete.contains("ALTER", Qt::CaseInsensitive) ||
            requete.contains("CREATE", Qt::CaseInsensitive) ||
            requete.contains("UPDATE", Qt::CaseInsensitive) ||
            requete.contains("INSERT", Qt::CaseInsensitive)){

        if (static_cast<MainWindow*>(this->parent())->getUtilisateur()->can(WRITE)){
            return true;
        }

    }
    else if (requete.contains("DROP", Qt::CaseInsensitive) ||
                requete.contains("TRUNCATE", Qt::CaseInsensitive) ||
                requete.contains("DELETE", Qt::CaseInsensitive)){

        if (static_cast<MainWindow*>(this->parent())->getUtilisateur()->can(DELETE)){
            return true;
        }

    }
    else{

        if (static_cast<MainWindow*>(this->parent())->getUtilisateur()->can(READ)){
            return true;
        }

    }


    return false;
}



