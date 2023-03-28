#include "bddtreeitem.h"
#include <algorithm>
#include "mainwindow.h"
#include "ui_visualisationbdd.h"
#include "visualisationbdd.h"

// Constructeur
/*
    * @brief Constructeur de la classe VisualisationBDD
    * @param parent : QWidget parent
*/
VisualisationBDD::VisualisationBDD(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::VisualisationBDD)
{
    profil = nullptr;
    currentDatabase = nullptr;

    ui->setupUi(this);
    ui->inputPath->setReadOnly(true);
    ui->vueTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->vueArborescence->setContextMenuPolicy(Qt::CustomContextMenu);

    contextMenu = new QMenu("Menu",ui->vueArborescence);
    delAction = new QAction("Supprimer",this);

    connect(ui->boutonSelection, SIGNAL(clicked()), SLOT(clickSelectionFichier()));
    connect(ui->boutonEffacer, SIGNAL(clicked()), SLOT(clickEffacer()));
    connect(ui->boutonExec, SIGNAL(clicked()), SLOT(clickExecuter()));
    connect(ui->boutonDeconnexion, SIGNAL(clicked()), SLOT(clickDeconnexion()));
    connect(ui->boutonChoixProfil, SIGNAL(clicked()), SLOT(clickChoixProfil()));
    connect(ui->vueArborescence, SIGNAL(itemDoubleClicked(QTreeWidgetItem*,int)), SLOT(clickTableArborescence(QTreeWidgetItem*,int)));
    connect(ui->vueArborescence, SIGNAL(customContextMenuRequested(QPoint)), SLOT(rightClickOnTreeItem(QPoint)));
    connect(delAction, SIGNAL(triggered(bool)), SLOT(removeCurrentItemFromTree()));
}

// Destructeur
/*
    * @brief Destructeur de la classe VisualisationBDD
*/
VisualisationBDD::~VisualisationBDD()
{
    delete ui;
    profil = nullptr;
    if (currentDatabase != nullptr) delete currentDatabase;
    delete contextMenu;
}

/*
    * @brief Fonction permettant de lier la fenêtre de visualisation à un profil courant
    * @param profil : Profil à lier
*/
void VisualisationBDD::attachProfile(Profil* profil)
{
    this->profil = profil;
}

/*
    * @ brief Méthode d'affichage d'une fenêtre de confirmation
    * @param titre : Titre de la fenêtre
    * @param description : Description de la fenêtre
    * @return int : Code de retour de la fenêtre
*/
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

/*
    * @brief Méthode d'initialisation de la fenêtre de visualisation
*/
void VisualisationBDD::init(){
    ui->inputPath->clear();
    ui->inputSQL->clear();
    if(ui->vueTable->model() != nullptr) static_cast<QSqlQueryModel*>(ui->vueTable->model())->clear();
    ui->vueArborescence->clear();

    CreateTree(this->profil);

}

/*
    * @brief Méthode de mise à jour de la base de données courante
    * @param db : Item de l'arborescence représentant la base de données
*/
void VisualisationBDD::setDatabase(BDDTreeItem* dbItem){
    if(dbItem != nullptr){
        for (int i = 0; i < ui->vueArborescence->topLevelItemCount(); i++){
            QTreeWidgetItem* it_item = ui->vueArborescence->topLevelItem(i);
            it_item->setBackground(0, QColor(255, 255, 255));
            it_item->setForeground(0, QColor(0, 0, 0));
        }
        dbItem->setBackground(0, QColor(255, 102, 0));
        dbItem->setForeground(0, QColor(255, 255, 255));
        this->currentDatabase = dbItem->getDatabase();
    }

}

/*
    * @brief Méthode permettant de chose un nouveau fichier de base de données à ajouté à l'arborescence
*/
void VisualisationBDD::clickSelectionFichier()
{
    QString cwd = QString::fromStdString(std::filesystem::current_path().string());

    // Generate a useless "+[CATransaction synchronize] called within transaction" warning on MacOS
    QString chemin = QFileDialog::getOpenFileName(this, tr("Sélection d'une base de données"), cwd, tr("Fichiers de bases de données (*.sqlite)"));
    ui->inputPath->setText(chemin);

    // Check if path is valid
    if (!QFile::exists(chemin))
    {
        return;
    }

    // Check if DB is already in TreeWidget
    const std::vector<QSqlDatabase> & databases = profil->getDatabases();
    for (auto it = databases.begin() ; it < databases.end() ; it++)
    {
        if (it->databaseName() == chemin)
        {
            QMessageBox::critical(0, "Erreur", "Cette base de données est déjà ouverte !");
            return;
        }
    }


    QSqlDatabase* db = new QSqlDatabase(QSqlDatabase::addDatabase("QSQLITE",chemin)); // where delete ?

    db->setDatabaseName(chemin);
    UpdateTree(db);


    // TODO handle errors
    Utilisateur& current_user = *((MainWindow*)this->parent())->getUtilisateur();

    profil->getDatabases().push_back(*db);

    ControleurXML::updateUser(current_user);
}

/*
    * @brief Slot permettant de vider le champ de saisie de la requête SQL lors de l'appui sur le bouton "Effacer"
*/
void VisualisationBDD::clickEffacer()
{
    ui->inputSQL->clear();
}

/*
    * @brief Slot permettant d'exécuter la requête SQL lors de l'appui sur le bouton "Exécuter"
*/
void VisualisationBDD::clickExecuter()
{
    const QString& commande = ui->inputSQL->text();
    if (currentDatabase == nullptr)
    {
        QMessageBox::warning(0, "Erreur d'accès", "Veuillez connecter une base de données");
        return;
    }
    if (commande == ""){
        QMessageBox::warning(0, "Erreur d'exécution", "Le champ est vide !");
        return;
    }
    std::cout<<currentDatabase->databaseName().toStdString() << std::endl;
    bool isOpen = currentDatabase->open();
    if (! isOpen){
        std::cout << currentDatabase->lastError().text().toStdString() << std::endl;
        return;
    }

    // permission = READ, WRITE, DELETE depending on the query, -1 if user has no right to execute the query
    int permission = checkRightToExecute(commande);
    if (permission == -1)
    {
        QMessageBox::critical(0, "Erreur d'exécution", "Vous n'avez pas les droits nécéssaires pour exécuter cette requête");
        return;
    }
    
    QSqlQuery* retourRequete = new QSqlQuery(*currentDatabase);
    retourRequete->exec(commande);



    if (retourRequete->size() == 0)
    {
        ui->vueTable->clearSpans();
        QMessageBox::information(0, "Information", "Le jeu de données retourné est vide :\n" + retourRequete->lastError().text(), QMessageBox::Ok, QMessageBox::Ok);
    }
    else
    {
        if (permission == READ)
        {
            QSqlQueryModel* modele = new QSqlQueryModel();
            modele->setQuery(std::move(*retourRequete));
            if(ui->vueTable->model() != nullptr)
            {
                //static_cast<QSqlQueryModel*>(ui->vueTable->model())->clear();
                ui->vueTable->clearSpans();
            }
            ui->vueTable->setModel(modele);
        }
        else if (permission == DELETE)
        {
            ui->vueTable->clearSpans();
        }
        else if (permission == WRITE)
        {
            if (ui->vueArborescence->currentItem()->parent() != nullptr)
            {
                retourRequete->exec("SELECT * FROM " + ui->vueArborescence->currentItem()->text(0));
                QSqlQueryModel* modele = new QSqlQueryModel();
                modele->setQuery(std::move(*retourRequete));
                if(ui->vueTable->model() != nullptr)
                {
                    static_cast<QSqlQueryModel*>(ui->vueTable->model())->clear();
                }
                ui->vueTable->setModel(modele);
            }
            ui->vueTable->clearSpans();
        }
    }

    currentDatabase->close();
}

/*
    * @brief Slot permettant de déconnecter l'utilisateur lors de l'appui sur le bouton "Déconnexion"
*/
void VisualisationBDD::clickDeconnexion()
{
    int reponse = fenetreConfirmation("Vous allez être déconnecté.", "Êtes-vous sûr de vouloir procéder à la déconnexion ?");

    if (reponse == QMessageBox::Yes)
    {
        this->hide();
        static_cast<MainWindow*>(this->parent())->deconnexion();
    }
}

/*
    * @brief Slot permettant de selectionner une base de données dans l'arborescence lors d'un clic sur un élément ou d'afficher la table sélectionnée
*/
void VisualisationBDD::clickTableArborescence(QTreeWidgetItem* item,int column){
    QString nom = item->text(column);

    if (item->parent() != nullptr)
    {
        std::cout<<static_cast<BDDTreeItem*>(item->parent())->text(0).toStdString() << std::endl;
        setDatabase(static_cast<BDDTreeItem*>(item->parent()));
        ui->inputSQL->setText("SELECT * FROM " + nom);
        clickExecuter();
    }
    else if (item->parent() == nullptr)
    {
        setDatabase(static_cast<BDDTreeItem*>(item));
    }

}

/*
    * @brief Slot permettant de lancer la fenêtre de choix de profil lors de l'appui sur le bouton "Changer de profil"
*/
void VisualisationBDD::clickChoixProfil(){
    static_cast<MainWindow*>(this->parent())->lancerChoixProfil(nullptr, CONTEXT_CHANGE_PROFILE);
}

/*
    * @brief Méthode permettant de vérifier si l'utilisateur a les droits d'exécution de la requête SQL
    * @param requete Requête SQL à vérifier
    * @return READ si l'utilisateur a les droits de lecture, WRITE si l'utilisateur a les droits d'écriture, DELETE si l'utilisateur a les droits de suppression, -1 si l'utilisateur n'a pas les droits d'exécution
*/
int VisualisationBDD::checkRightToExecute(QString requete)
{
    if (requete.contains("ADD", Qt::CaseInsensitive) ||
        requete.contains("ALTER", Qt::CaseInsensitive) ||
        requete.contains("CREATE", Qt::CaseInsensitive) ||
        requete.contains("UPDATE", Qt::CaseInsensitive) ||
        requete.contains("INSERT", Qt::CaseInsensitive))
    {

        if (static_cast<MainWindow*>(this->parent())->getUtilisateur()->can(WRITE))
        {
            return WRITE;
        }

    }
    else if (requete.contains("DROP", Qt::CaseInsensitive) ||
             requete.contains("TRUNCATE", Qt::CaseInsensitive) ||
             requete.contains("DELETE", Qt::CaseInsensitive))
    {
        if (static_cast<MainWindow*>(this->parent())->getUtilisateur()->can(DELETE))
        {
            return DELETE;
        }

    }
    else
    {

        if (static_cast<MainWindow*>(this->parent())->getUtilisateur()->can(READ))
        {
            return READ;
        }

    }

    return -1;
}

/*
    * @brief Méthode permettant de créer l'arborescence des bases de données
    * @param profil Profil à traiter
*/
void VisualisationBDD::CreateTree(Profil* profil)
{
    ui->vueArborescence->clear();
    ui->vueArborescence->setColumnCount(1);
    QList<QTreeWidgetItem*> elements;

    for (std::vector<QSqlDatabase>::size_type i = 0 ; i < profil->getDatabases().size() ; i++)
    {
        //afficher le nom de chaque base de données
        std::string nom = profil->getDatabases().at(i).databaseName().toStdString();
        elements.append(new BDDTreeItem(&(profil->getDatabases().at(i))));


        //afficher les noms des tables dans chaque base de données
        QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE","connecCreate");
        db.setDatabaseName(profil->getDatabases().at(i).databaseName());

        if (db.open())
        {
            std::cout << "c'est ouvert" << std::endl;
            QSqlQuery q(db);
            q.exec("SELECT name FROM sqlite_schema WHERE type='table' ORDER BY name");
            //int j = 0;
            while(q.next())
            {
                QString name = q.value(0).toString();
                elements.append(new QTreeWidgetItem(elements.at(i), QStringList(QString(name))));
            }
        }
        else
        {
            std::cout << "Erreur ouverture BDD" << std::endl;
        }
        db.close();


    }
    ui->vueArborescence->insertTopLevelItems(0, elements);

    BDDTreeItem* bddItem = static_cast<BDDTreeItem*>(ui->vueArborescence->topLevelItem(0));
    setDatabase(bddItem);
}

/*
    * @brief Méthode permettant d'ajouter un item dans l'arborescence des bases de données
    * @param db : QSqlDatabase
*/
void VisualisationBDD::UpdateTree(QSqlDatabase* db)
{
    QList<QTreeWidgetItem*> elements;
    bool ok = db->open();

    if (ok)
    {
        std::string nom = db->databaseName().toStdString();
        elements.append(new BDDTreeItem(db));
        QSqlQuery q(*db);
        q.exec("SELECT name FROM sqlite_schema WHERE type='table' ORDER BY name");
        int i = 0;
        while(q.next())
        {
            QString name = q.value(0).toString();
            elements.append(new QTreeWidgetItem(elements.at(i), QStringList(QString(name))));
        }
    }
    else
    {
        std::cout << "Erreur ouverture bdd" << std::endl;
    }
    db->close();
    ui->vueArborescence->insertTopLevelItems(0, elements);
    BDDTreeItem* bddItem = static_cast<BDDTreeItem*>(ui->vueArborescence->topLevelItem(0));
    setDatabase(bddItem);
}

/*
    * @brief Méthode permettant de supprimer un item de l'arborescence des bases de données lors d'un clic droit
    * @param idx : QPoint
*/
void VisualisationBDD::rightClickOnTreeItem(QPoint idx)
{
    QModelIndex index = ui->vueArborescence->indexAt(idx);


    if(index.isValid()) // Si on clique sur un item et que l'item est une bdd
    {
        contextMenu->addAction(delAction);
        contextMenu->exec(QCursor::pos());
    }
}

/*
    * @brief Méthode permettant de supprimer un item de l'arborescence des bases de données
*/
void VisualisationBDD::removeCurrentItemFromTree()
{

    // TODO
    // 1 - le supprimer de l'arbre
    QTreeWidgetItem* item = ui->vueArborescence->currentItem();
    if (item->parent() == nullptr)
    {
        QSqlDatabase* db = static_cast<BDDTreeItem*>(item)->getDatabase();
        QString itemName = item->text(0);

        qDebug() << db->databaseName();

        for (auto db_iterator = profil->getDatabases().begin(); db_iterator != profil->getDatabases().end(); db_iterator++){
            if (db->databaseName().compare(db_iterator->databaseName()) == 0){
                profil->getDatabases().erase(db_iterator);
                QMessageBox::information(0, "", "La base de données '" + itemName + "' a été supprimée de la liste attachée à votre profil.");
                ControleurXML::updateUser(*static_cast<MainWindow*>(this->parent())->getUtilisateur());
                break;
            }
        }
        delete item;

    }
    else
    {
        if (static_cast<MainWindow*>(this->parent())->getUtilisateur()->can(DELETE)){
            QString nomTable = item->text(0);

            int choix = fenetreConfirmation("Avertissement", "Êtes vous sur de vouloir supprimer (DROP) la table '" + nomTable + "' de la base de données ?");

            if(choix == QMessageBox::Yes){
                ui->inputSQL->setText("DROP TABLE " + nomTable);
                clickExecuter();
                delete item;
            }
        }
    }
}

