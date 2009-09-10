#include <QMimeData>
#include "bttreemodel.h"
#include "btnode.h"
#include "btnodetype.h"
#include <qmessagebox.h>
#include "btbrain.h"
#include "btdecoratornode.h"

btTreeModel::btTreeModel(QObject* parent, btBrain* containingBrain)
    : QAbstractItemModel(parent)
{
    m_rootNode = new btNode();
    brain = containingBrain;
}

btTreeModel::~btTreeModel()
{
    delete(m_rootNode);
}

void btTreeModel::setRootNode(btNode *newRoot)
{
    delete(m_rootNode);
    m_rootNode = newRoot;
    reset();
}

btNode * btTreeModel::rootNode() const
{
    return m_rootNode;
}

QModelIndex btTreeModel::index(int row, int column, const QModelIndex &parent) const
{
    // If we don't have a root node, we need to return an empty QModelIndex
    if(!m_rootNode)
        return QModelIndex();
    btNode *parentNode = nodeFromIndex(parent);
    return createIndex(row, column, parentNode->child(row));
}

btNode *btTreeModel::nodeFromIndex(const QModelIndex &index) const
{
    if(index.isValid())
        return static_cast<btNode*>(index.internalPointer());
    else
        return m_rootNode;
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

	if(parentNode == m_rootNode)
		return QModelIndex();

    return createIndex(parentNode->row(), child.column(), parentNode);
}

QVariant btTreeModel::data(const QModelIndex &index, int role) const
{
    btNode *node = nodeFromIndex(index);
    if(!node)
        return QVariant();
    
    if(role == Qt::DisplayRole)
    {
        return node->data(index.column());
    }
    else if(role == Qt::ToolTipRole)
    {
        QString tip;
        tip = "<html>";
        tip += tr("Decorators: %1").arg(node->decoratorCount());
        tip += "<table>";
        foreach(btDecoratorNode* theNode, node->decorators())
            tip += "<tr><td>" + theNode->name() + "</td><td>" + theNode->description() + "</td></tr>";
        tip += "</table>";
        tip += "</html>";
        return tip;
    }
    else
        return QVariant();
}

bool btTreeModel::setData ( const QModelIndex & index, const QVariant & value, int role )
{
}

QVariant btTreeModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    Q_UNUSED(orientation);
    if(role == Qt::DisplayRole)
        m_rootNode->headerData(section);
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
    
    while(!stream.atEnd())
    {
        QString nodeType;
        QString btType;
        stream >> nodeType;
        stream >> btType;
        nodeTypes.insert(nodeType, btType);
    }

    btNode* parentNode = static_cast<btNode*>(parent.internalPointer());
    int rows = 0;
    QList<btNodeType*> theNodeTypes;
    QHashIterator<QString, QString> i(nodeTypes);
    while (i.hasNext())
    {
        i.next();
        btNodeType *theNodeType = brain->findNodeTypeByName(i.value());
        theNodeType->setName(i.key());
        theNodeType->setParent(this);
        theNodeTypes.append(theNodeType);
        if(theNodeType->type() != btNodeType::DecoratorNodeType)
            ++rows;
    }

    // Yes, this is kinda nasty - but we may well be dropping decorators, which are not true children
    if(rows > 0)
        beginInsertRows(parent, parentNode->childCount(), rows);
    foreach(btNodeType* theNodeType, theNodeTypes)
    {
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
    if(rows > 0)
        endInsertRows();
    else
        emit dataChanged(parent, parent);//Update the view for the parent node we have (likely) just added a decorator to

    return true;
}

void btTreeModel::setName(QString name) { m_name = name; }
QString btTreeModel::name() const { return m_name; }

#include "bttreemodel.moc"
