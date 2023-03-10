#include "controleurxml.h"

std::vector<Utilisateur> ControleurXML::parseFile()
{
    std::vector<Utilisateur> users;

    QFile file(FILENAME);
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text)){
        qDebug() << "File opening failed !";
    }

    QDomDocument xmlBOM = openDocument(FILENAME);

    // Extract the root markup
    QDomElement root=xmlBOM.documentElement();

    // Get the first child of the root (Markup COMPONENT is expected)
    QDomElement userComponent=root.firstChild().toElement();

    while(!userComponent.isNull())
    {
        // Check if the child tag name is COMPONENT
        if (userComponent.tagName() == "USER")
            users.push_back(createUserFromXMLComponent(userComponent));

        // Next component
        userComponent = userComponent.nextSibling().toElement();
    }

    // TODO : MAYBE MOVE ADMIN CREATION =========
    if (users.size() == 0)
    {
        Utilisateur admin("admin","admin","admin@admin.admin","admin");
        admin.addPermission(READ);
        admin.addPermission(WRITE);
        admin.addPermission(DELETE);
        admin.addProfil(Profil("Profil_1"));
        admin.addProfil(Profil("Profil_2"));

        users.push_back(admin);
        ControleurXML::writeFile(users);
    }
    // =========  END OF ADMIN CREATION =========


    return users;
}


bool ControleurXML::writeFile(std::vector<Utilisateur> users)
{
    // Create a document to write XML
    QDomDocument document;

    // Making the root element
    QDomElement root = document.createElement("USERDATABASE");

    for (auto it = users.begin() ; it < users.end() ; it++) {

        QDomElement user = document.createElement("USER");

        QDomElement prenom = document.createElement("FIRSTNAME");
        QDomElement nom = document.createElement("LASTNAME");
        QDomElement mail = document.createElement("MAIL");
        QDomElement mdp = document.createElement("PASSWORD");
        QDomElement permissions = document.createElement("PERMISSIONS");
        QDomElement profils = document.createElement("PROFILS");

        prenom.appendChild(document.createTextNode(it->getPrenom().c_str()));
        nom.appendChild(document.createTextNode(it->getNom().c_str()));
        mail.appendChild(document.createTextNode(it->getMail().c_str()));
        mdp.appendChild(document.createTextNode(it->getPassword().c_str()));
        permissions.setAttribute("read", QString::number(it->can(READ)));
        permissions.setAttribute("write", QString::number(it->can(WRITE)));
        permissions.setAttribute("delete", QString::number(it->can(DELETE)));

        std::vector<Profil> userProfils = it->getProfils();

        for (auto it2 = userProfils.begin() ; it2 < userProfils.end() ; it2++)
        {
            std::string nomProfil = it2->getNomProfil();
            QDomElement profilComponent = document.createElement("PROFIL");
            profilComponent.setAttribute("name", QString::fromStdString(nomProfil));
            profils.appendChild(profilComponent);
        }

        user.appendChild(prenom);
        user.appendChild(nom);
        user.appendChild(mail);
        user.appendChild(mdp);
        user.appendChild(permissions);
        user.appendChild(profils);

        root.appendChild(user);
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


Utilisateur ControleurXML::createUserFromXMLComponent(QDomElement component)
{
    Utilisateur user;

    QDomElement userAttribute = component.firstChild().toElement();

    while (!userAttribute.isNull())
    {
        if (userAttribute.tagName() == "FIRSTNAME")
            user.setPrenom(userAttribute.firstChild().toText().data().toStdString());

        if (userAttribute.tagName() == "FIRSTNAME")
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
                if (userAttribute.tagName() == "PROFIL")
                {
                    Profil profil(profilComponent.attribute("name").toStdString());
                    user.addProfil(profil);
                }
                profilComponent = profilComponent.nextSibling().toElement();
            }
        }


        userAttribute = userAttribute.nextSibling().toElement();
    }

    return user;
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
    // R??cup??ration des utilisateurs existants
    std::vector<Utilisateur> users = ControleurXML::parseFile();

    // V??rification
    for (auto it = users.begin() ; it < users.end() ; it++)
    {
        if (*it == user) // Si il existe d??j??
        {
            return false;
        }
    }

    // Il n'existe pas d??j??
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
    // R??cup??ration des utilisateurs existants
    std::vector<Utilisateur> users = ControleurXML::parseFile();

    // V??rification
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
    // R??cup??ration des utilisateurs existants
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
