#ifndef BDDTREEITEM_H
#define BDDTREEITEM_H


#include "QtCore/qdir.h"
#include "QtSql/qsqldatabase.h"
#include "QtWidgets/qtreewidget.h"


class BDDTreeItem : public QTreeWidgetItem
{
private:
    QSqlDatabase* database;

public:
    BDDTreeItem(QSqlDatabase* database)
        : QTreeWidgetItem(static_cast<QTreeWidget*>(nullptr), QStringList(database->databaseName().split(QDir::separator()).last()))
    {
        setDatabase(database);
    }

    QSqlDatabase* getDatabase() {return database;}
    void setDatabase(QSqlDatabase* database) {this->database = database;}
};

#endif // BDDTREEITEM_H
