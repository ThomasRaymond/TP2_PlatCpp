#ifndef BDDTREEITEM_H
#define BDDTREEITEM_H


#include "QtCore/qdir.h"
#include "QtSql/qsqldatabase.h"
#include "QtWidgets/qtreewidget.h"


// Classe permettant de stocker les informations d'une base de données dans un QTreeWidgetItem
class BDDTreeItem : public QTreeWidgetItem
{
private:
    QSqlDatabase* database;

public:
    BDDTreeItem(QSqlDatabase* database)
        : QTreeWidgetItem(static_cast<QTreeWidget*>(nullptr), QStringList(database->databaseName().split('/').last().split('.').first()))
    {
        setDatabase(database);
    }

    ~BDDTreeItem(){
        delete database;
    }

    QSqlDatabase* getDatabase() {return database;}
    void setDatabase(QSqlDatabase* database) {this->database = database;}
};

#endif // BDDTREEITEM_H
