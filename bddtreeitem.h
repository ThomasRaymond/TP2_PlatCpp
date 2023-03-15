#ifndef BDDTREEITEM_H
#define BDDTREEITEM_H


#include "QtSql/qsqldatabase.h"
#include "QtWidgets/qtreewidget.h"


class BDDTreeItem : public QTreeWidgetItem
{
private:
    QSqlDatabase* database;

public:
    BDDTreeItem(QSqlDatabase* database) {setDatabase(database);}

    QSqlDatabase* getDatabase() {return database;}
    void setDatabase(QSqlDatabase* database) {this->database = database}
};

#endif // BDDTREEITEM_H
