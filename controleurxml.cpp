#include "controleurxml.h"

std::vector<Utilisateur> ControleurXML::parseFile()
{
    std::vector<Utilisateur> users;

    QDomDocument xmlBOM = openDocument("/Users/thomasraymond/Documents/Etudes/DI4/S8/Plateformes logicielles/Plateformes logicielles C++/TP2/users.xml");

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

    return users; // TODO
}


bool ControleurXML::writeFile(std::vector<Utilisateur>)
{
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
            user.setMail(userAttribute.firstChild().toText().data().toStdString());

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
