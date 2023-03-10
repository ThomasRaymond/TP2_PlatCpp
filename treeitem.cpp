#include "treeitem.h"

TreeItem::TreeItem(const QList<QVariant> &data, TreeItem *parentItem = nullptr)
    : itemData(data), parentItem(data)
{}

TreeItem::~TreeItem()
{
    qDeleteAll(childItems);
}

void TreeItem::appendChild(TreeItem *item)
{
    childItems.append(item);
}

TreeItem *TreeItem::child(int row)
{
    if (row < 0 || row >= childItems.size())
        return nullptr;
    return childItems.at(row);
}

int TreeItem::childCount()
{
    return childItems.count();
}

int TreeItem::row()
{
    //TODO
}

int TreeItem::columnCount()
{
    itemData.count();
}

QVariant TreeItem::data(int column)
{
    if (column < 0 || column >= itemData.size())
        return QVariant();
    return itemData.at(column);
}

TreeItem *TreeItem::parentItem()
{
    return parentItem;
}
