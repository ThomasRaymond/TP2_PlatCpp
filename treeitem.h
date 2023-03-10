#ifndef TREEITEM_H
#define TREEITEM_H


class TreeItem
{
private:
    QList<TreeItem *> childItems;
    QList<QVariant> itemData;
    TreeItem *parentItem;

public:
    TreeItem(const QList<QVariant> &data, TreeItem *parentItem = nullptr);
    ~TreeItem();

    void appendChild(TreeItem *child);

    TreeItem *child(int row);
    int childCount();
    int columnCount();
    QVariant data(int column);
    int row();
    TreeItem *parentItem();
};

#endif // TREEITEM_H
