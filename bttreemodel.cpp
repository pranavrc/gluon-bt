#include <QMimeData>
#include "bttreemodel.h"
#include "btnode.h"
#include "btnodetype.h"
#include <qmessagebox.h>
#include "btbrain.h"

btTreeModel::btTreeModel(QObject* parent, btBrain* containingBrain)
    : QAbstractItemModel(parent)
{
    rootNode = new btNode();
    brain = containingBrain;
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

bool btTreeModel::setData ( const QModelIndex & index, const QVariant & value, int role )
{
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

Qt::ItemFlags btTreeModel::flags(const QModelIndex &index) const
{
    Qt::ItemFlags defaultFlags = QAbstractItemModel::flags(index);
    Qt::ItemFlags thisIndexFlags;
    
    if (index.isValid())
    {
        thisIndexFlags = Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsDragEnabled | Qt::ItemIsDropEnabled | defaultFlags;
    }
    else
        thisIndexFlags = Qt::ItemIsEnabled | Qt::ItemIsDropEnabled | defaultFlags;
    
    return thisIndexFlags;
}

QStringList btTreeModel::mimeTypes() const
{
    QStringList types;
    types << "application/bt.nodetype";
    return types;
}

bool btTreeModel::dropMimeData(const QMimeData *data, Qt::DropAction action, int row, int column, const QModelIndex &parent)
{
    if(action == Qt::IgnoreAction)
        return true;
    
    if(!data->hasFormat("application/bt.nodetype"))
        return false;
    
    if(column > 0)
        return false;
    
    // We only do the parent thing here - we accept no drops in empty space at all
    if(!parent.isValid())
        return false;
    
    QByteArray encodedData = data->data("application/bt.nodetype");
    QDataStream stream(&encodedData, QIODevice::ReadOnly);
    QHash<QString,QString> nodeTypes;
    int rows = 0;
    
    while(!stream.atEnd())
    {
        QString nodeType;
        QString btType;
        stream >> nodeType;
        stream >> btType;
        nodeTypes.insert(nodeType, btType);
        ++rows;
    }

    btNode* parentNode = static_cast<btNode*>(parent.internalPointer());
    insertRows(parent.row(), rows, parent);
    QHashIterator<QString, QString> i(nodeTypes);
    while (i.hasNext()) {
        i.next();
        btNodeType *theNodeType = brain->findNodeTypeByName(i.value());
        theNodeType->setName(i.key());
        theNodeType->setParent(this);
        // Figure out whether the dropped item is a special case (decorators are added to the parent item directly, rather than added as children)
        if(theNodeType->type() == btNodeType::DecoratorNodeType)
        {
            parentNode->addDecorator(qobject_cast<btDecoratorNode*>(theNodeType));
        }
        else
        {
            btNode *newChild = new btNode(theNodeType, parentNode);
            newChild->setName(tr("New %1").arg(theNodeType->name()));
        }
    }
    return true;
}

void btTreeModel::setName(QString name) { m_name = name; }
QString btTreeModel::name() const { return m_name; }

#include "bttreemodel.moc"
