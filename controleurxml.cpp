#include "controleurxml.h"

std::vector<Utilisateur> ControleurXML::parseFile()
{
    std::vector<Utilisateur> users;

    QFile file(FILENAME);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "File opening failed !";

        //try to create it
        if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            qDebug() << "Cannot create file !";
            throw std::exception();
        }
    }

    QDomDocument xmlBOM = openDocument(FILENAME);

    // Extract the root markup
    QDomElement root=xmlBOM.documentElement();

    // Get the first child of the root (Markup USER is expected)
    QDomElement userComponent=root.firstChild().toElement();

    while(!userComponent.isNull())
    {
        // Check if the child tag name is USER
        if (userComponent.tagName() == "USER")
            users.push_back(UtilisateurFromQDom(userComponent));

        // Next component
        userComponent = userComponent.nextSibling().toElement();
    }

    return users;
}


bool ControleurXML::writeFile(std::vector<Utilisateur> users)
{
    // Create a document to write XML
    QDomDocument document;

    // Making the root element
    QDomElement root = document.createElement("USERDATABASE");

    for (auto it = users.begin() ; it < users.end() ; it++)
    {
        root.appendChild(QDomElemFromUtilisateur(*it,document));
    }

    // Adding the root element to the docuemnt
    document.appendChild(root);

    // Writing to a file

    QFile file(FILENAME);
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        qDebug() << "Open the file for writing failed";
    }
    else
    {
        QTextStream stream(&file);
        stream << document.toString();
        file.close();
        qDebug() << "Writing is done";
    }

    return true; // TODO
}

QDomDocument ControleurXML::openDocument(std::string path)
{
    QDomDocument xmlBOM;
    // Load xml file as raw data
    QFile f(path.c_str()); // TODO : use in argument
    if (!f.open(QIODevice::ReadOnly ))
    {
        // Error while loading file
        std::cerr << "Error while loading file" << std::endl;
        throw std::exception();
    }
    // Set data into the QDomDocument before processing
    xmlBOM.setContent(&f);
    f.close();

    return xmlBOM;
}


bool ControleurXML::addUser(Utilisateur user)
{
    // Récupèration des utilisateurs existants
    std::vector<Utilisateur> users = ControleurXML::parseFile();

    // Vérification
    for (auto it = users.begin() ; it < users.end() ; it++)
    {
        if (*it == user) // Si il existe déjà
        {
            return false;
        }
    }

    // Il n'existe pas déjà
    // Ajout du nouvel utilisateur aux utilisateurs existants
    users.push_back(user);

    // Ecriture du fichier
    if (!ControleurXML::writeFile(users))
    {
        return false;
    }

    return true;
}


Utilisateur* ControleurXML::verifyUser(std::string login, std::string password)
{
    // Récupèration des utilisateurs existants
    std::vector<Utilisateur> users = ControleurXML::parseFile();

    // Vérification
    for (auto it = users.begin() ; it < users.end() ; it++)
    {
        if (it->getMail() == login && it->getPassword() == password) // Si il y a une correspondance
        {
            return new Utilisateur(*it);
        }
    }

    return nullptr;

}

int ControleurXML::nombreUtilisateurs()
{
    // Récupération des utilisateurs existants
    std::vector<Utilisateur> users = ControleurXML::parseFile();

    return users.size();
}


// Can use newUser for both if user.mail has not changed
bool ControleurXML::updateUser(const Utilisateur & oldUser, const Utilisateur & newUser)
{
    std::vector<Utilisateur> users = ControleurXML::parseFile();

    for (std::vector<Utilisateur>::size_type i = 0 ; i < users.size() ; i++)
    {
        if (users.at(i) == oldUser)
        {
            users.erase(users.begin()+i);
            users.push_back(newUser);
            ControleurXML::writeFile(users);
            return true;
        }
    }

    return false;
}

/* ------------ */

QDomElement ControleurXML::QDomElemFromUtilisateur(Utilisateur & user, QDomDocument & document)
{
    QDomElement user_qdom = document.createElement("USER");

    QDomElement prenom = document.createElement("FIRSTNAME");
    QDomElement nom = document.createElement("LASTNAME");
    QDomElement mail = document.createElement("MAIL");
    QDomElement mdp = document.createElement("PASSWORD");
    QDomElement permissions = document.createElement("PERMISSIONS");
    QDomElement profils = document.createElement("PROFILS");

    prenom.appendChild(document.createTextNode(user.getPrenom().c_str()));
    nom.appendChild(document.createTextNode(user.getNom().c_str()));
    mail.appendChild(document.createTextNode(user.getMail().c_str()));
    mdp.appendChild(document.createTextNode(user.getPassword().c_str()));
    //profils.appendChild(document.createTextNode(""));
    permissions.setAttribute("read", QString::number(user.can(READ)));
    permissions.setAttribute("write", QString::number(user.can(WRITE)));
    permissions.setAttribute("delete", QString::number(user.can(DELETE)));

    std::vector<Profil> userProfils = user.getProfils();

    for (auto it = userProfils.begin() ; it < userProfils.end() ; it++)
    {
        profils.appendChild(QDomElemFromProfil(*it,document));
    }

    user_qdom.appendChild(prenom);
    user_qdom.appendChild(nom);
    user_qdom.appendChild(mail);
    user_qdom.appendChild(mdp);
    user_qdom.appendChild(permissions);
    user_qdom.appendChild(profils);

    return user_qdom;
}

Utilisateur ControleurXML::UtilisateurFromQDom(QDomElement & qdom)
{
    Utilisateur user;

    QDomElement userAttribute = qdom.firstChild().toElement();

    while (!userAttribute.isNull())
    {
        if (userAttribute.tagName() == "FIRSTNAME")
            user.setPrenom(userAttribute.firstChild().toText().data().toStdString());

        if (userAttribute.tagName() == "LASTNAME")
            user.setNom(userAttribute.firstChild().toText().data().toStdString());

        if (userAttribute.tagName() == "MAIL")
            user.setMail(userAttribute.firstChild().toText().data().toStdString());

        if (userAttribute.tagName() == "PASSWORD")
            user.setPassword(userAttribute.firstChild().toText().data().toStdString());

        if (userAttribute.tagName() == "PERMISSIONS")
        {
            if (userAttribute.attribute("read") == "1")
            {
                user.addPermission(READ);
            }
            if (userAttribute.attribute("write") == "1")
            {
                user.addPermission(WRITE);
            }
            if (userAttribute.attribute("delete") == "1")
            {
                user.addPermission(DELETE);
            }
        }

        if (userAttribute.tagName() == "PROFILS")
        {
            QDomElement profilComponent = userAttribute.firstChild().toElement();

            while(!profilComponent.isNull())
            {
                if (profilComponent.tagName() == "PROFIL")
                {
                    user.addProfil(ProfilFromQDom(profilComponent));
                }
                profilComponent = profilComponent.nextSibling().toElement();
            }
        }

        userAttribute = userAttribute.nextSibling().toElement();
    }

    return user;
}

QDomElement ControleurXML::QDomElemFromProfil(Profil & profil, QDomDocument & document)
{
    QDomElement profil_qdom = document.createElement("PROFIL");

    profil_qdom.setAttribute("name", QString::fromStdString(profil.getNomProfil()));

    std::vector<QSqlDatabase> databases = profil.getDatabases();

    for (auto it = databases.begin() ; it < databases.end() ; it++)
    {
        profil_qdom.appendChild(QDomElemFromDatabase(*it,document));
    }

    return profil_qdom;
}

Profil ControleurXML::ProfilFromQDom(QDomElement & qdom)
{
    Profil profil(qdom.attribute("name").toStdString());

    QDomElement databaseComponent = qdom.firstChild().toElement();

    while(!databaseComponent.isNull())
    {
        if (qdom.tagName() == "PROFIL")
        {
            profil.getDatabases().push_back(DatabaseFromQDom(databaseComponent));
        }
        databaseComponent = databaseComponent.nextSibling().toElement();
    }

    return profil;
}


QDomElement ControleurXML::QDomElemFromDatabase(QSqlDatabase & database, QDomDocument & document)
{
    QDomElement database_qdom = document.createElement("DATABASE");

    database_qdom.setAttribute("path", database.databaseName());

    return database_qdom;
}

QSqlDatabase ControleurXML::DatabaseFromQDom(QDomElement & qdom)
{
    QSqlDatabase database = QSqlDatabase::addDatabase("QSQLITE","connecXML");

    database.setDatabaseName(qdom.attribute("path"));

    return database;
}
