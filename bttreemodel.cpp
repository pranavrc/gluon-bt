#include "bttreemodel.h"
#include "btnode.h"
#include "btnodetype.h"

btTreeModel::btTreeModel(QObject* parent)
{
    rootNode = new btNode();
}

btTreeModel::~btTreeModel()
{
    delete(rootNode);
}

void btTreeModel::setRootNode(btNode *newRoot)
{
    delete(rootNode);
    rootNode = newRoot;
    reset();
}

QModelIndex btTreeModel::index(int row, int column, const QModelIndex &parent) const
{
    // If we don't have a root node, we need to return an empty QModelIndex
    if(!rootNode)
        return QModelIndex();
    btNode *parentNode = nodeFromIndex(parent);
    return createIndex(row, column, parentNode->child(row));
}

btNode *btTreeModel::nodeFromIndex(const QModelIndex &index) const
{
    if(index.isValid())
        return static_cast<btNode*>(index.internalPointer());
    else
        return rootNode;
}

int btTreeModel::rowCount(const QModelIndex &parent) const
{
    btNode *parentNode = nodeFromIndex(parent);
    if(!parentNode)
        return 0;
    return parentNode->childCount();
}

int btTreeModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return 2;
}

QModelIndex btTreeModel::parent(const QModelIndex &child) const
{
    btNode *node = nodeFromIndex(child);
    if(!node)
        return QModelIndex();

    btNode *parentNode = node->parent();
    if(!parentNode)
        return QModelIndex();

	if(parentNode == rootNode)
		return QModelIndex();

    return createIndex(parentNode->row(), child.column(), parentNode);
}

QVariant btTreeModel::data(const QModelIndex &index, int role) const
{
    if(role != Qt::DisplayRole)
        return QVariant();

    btNode *node = nodeFromIndex(index);
    if(!node)
        return QVariant();

    if(index.column() == 0)
        return node->name();
    else
        return node->type()->name();

    return QVariant();
}

QVariant btTreeModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(orientation == Qt::Horizontal && role == Qt::DisplayRole)
    {
        if(section == 0)
            return tr("Name");
        else if(section == 1)
            return tr("Description");
        else if(section == 2)
            return tr("Type");
    }
    return QVariant();
}

void btTreeModel::setName(QString name) { m_name = name; }
QString btTreeModel::name() const { return m_name; }

#include "bttreemodel.moc"
