#include <QObject>
#include "btavailablenodesmodel.h"

btAvailableNodesModel::btAvailableNodesModel(QObject *parent)
        : QAbstractProxyModel(parent)
{
    categories.insert(btNodeType::ActionNodeType
, "Action");
    categories.insert(btNodeType::ConditionNodeType
, "Condition");
    categories.insert(btNodeType::CompositeNodeType
, "Composite");
    categories.insert(btNodeType::DecoratorNodeType
, "Decorator");
    categories.insert(btNodeType::ReferenceNodeType
, "Reference");
}

QModelIndex btAvailableNodesModel::mapFromSource(const QModelIndex &sourceIndex) const
{
    return index(sourceIndex.row(), sourceIndex.column());
}

QModelIndex btAvailableNodesModel::mapToSource(const QModelIndex &proxyIndex) const
{
    if(!proxyIndex.isValid())
        return QModelIndex();

    return sourceModel()->index(proxyIndex.row(), proxyIndex.column());
}

QModelIndex btAvailableNodesModel::index(int row, int column, const QModelIndex &parent) const
{
    // If we have a parent, we know (since this is only a two level tree) that it must have no children, and as such, this would not be possible
    if(!parent.isValid())
    {
        btNodeType *child = new btNodeType();
        createIndex(row, column, child);
    }

    // If the parent is not valid, it's one of the categories...
    btNodeType *childItem = new btNodeType();
    childItem->setName("Blab");
/*    int sourceIndex = 0, itemCount = 0;
    while(itemCount < row)
    {
        sourceIndex++;
        childItem = (btNodeType *)mapToSource(createIndex(sourceIndex, 0)).internalPointer();
        if( childItem->category() == parent.row())
            itemCount++;
    }*/

    return createIndex(row, column, childItem);
}

QModelIndex btAvailableNodesModel::parent(const QModelIndex &index) const
{
    if(!index.isValid())
        return QModelIndex();

    QModelIndex sourceIndex = mapToSource(index);

    // If we have one of the extra nodes, then it's a root node...
    int itemCount = sourceModel()->rowCount(QModelIndex());
    if(index.row() >= itemCount)
        return QModelIndex();

    // If we're inside the normal size, we're have a normal item. Now we just need to figure out which of the five to point at!
    QModelIndex tempIndex = createIndex(index.row(), 3, 0);
    int offset = sourceModel()->data(tempIndex, Qt::DisplayRole).toInt();
    return createIndex(itemCount + offset, index.column(), 0);
}

int btAvailableNodesModel::rowCount(const QModelIndex &parent) const
{
    // If we /do/ have a parent, then we need to look inside one of the categories...
    if(parent.isValid())
    {
        return 1;
    }

    // Otherwose it's just the root, and that is, of course, the categories...
    return categories.count();
}

int btAvailableNodesModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return 1;
}

QVariant btAvailableNodesModel::data(const QModelIndex &index, int role) const
{
    if(role != Qt::DisplayRole)
        return QVariant();

    if(!index.isValid())
        return QVariant();

    int itemCount = sourceModel()->rowCount(QModelIndex());
    if(index.row() >= itemCount)
    {
        int category = btNodeType::ActionNodeType
;
        category = index.row() - itemCount;
        return categories[category];
    }

    QModelIndex sourceIndex = mapToSource(index);
    return sourceModel()->data(sourceIndex, role);
}

#include "btavailablenodesmodel.moc"
