#include <QMimeData>
#include "bteditornodetype.h"
#include "btnodetypesmodelnode.h"
#include "btnodetypesmodel.h"
#include "btbrain.h"
#include <qmessagebox.h>

btNodeTypesModel::btNodeTypesModel(btBrain *brain, QObject* parent)
        :QAbstractItemModel(parent)
{
    rootNode = new btNodeTypesModelNode();
    rootNode->setName("Root node");

    nodeAction = new btNodeTypesModelNode();
    nodeAction->setName(tr("Action"));
    btEditorNodeType* nodeActionType = new btEditorNodeType();
    nodeActionType->setChildTypes(btNodeType::ActionNodeType);
    nodeAction->setNodeType(nodeActionType);
    rootNode->appendChild(nodeAction);

    nodeCondition = new btNodeTypesModelNode();
    nodeCondition->setName(tr("Condition"));
    btEditorNodeType* nodeConditionType = new btEditorNodeType();
    nodeConditionType->setChildTypes(btNodeType::ConditionNodeType);
    nodeCondition->setNodeType(nodeConditionType);
    rootNode->appendChild(nodeCondition);

    nodeComposite = new btNodeTypesModelNode();
    nodeComposite->setName(tr("Composite"));
    rootNode->appendChild(nodeComposite);

    nodeDecorator = new btNodeTypesModelNode();
    nodeDecorator->setName(tr("Decorator"));
    rootNode->appendChild(nodeDecorator);

    nodeReference = new btNodeTypesModelNode();
    nodeReference->setName(tr("Reference"));
    rootNode->appendChild(nodeReference);

    btNodeTypesModelNode *node;
    foreach(btNodeType *nodeType, brain->nodeTypes)
    {
        switch(nodeType->type())
        {
            case btNodeType::ActionNodeType
:
                node = new btNodeTypesModelNode(qobject_cast<btEditorNodeType*>(nodeType), nodeAction);
                break;
            case btNodeType::ConditionNodeType
:
                node = new btNodeTypesModelNode(qobject_cast<btEditorNodeType*>(nodeType), nodeCondition);
                break;
            case btNodeType::CompositeNodeType
:
                node = new btNodeTypesModelNode(qobject_cast<btEditorNodeType*>(nodeType), nodeComposite);
                break;
            case btNodeType::DecoratorNodeType
:
                node = new btNodeTypesModelNode(qobject_cast<btEditorNodeType*>(nodeType), nodeDecorator);
                break;
            case btNodeType::ReferenceNodeType
:
                node = new btNodeTypesModelNode(qobject_cast<btEditorNodeType*>(nodeType), nodeReference);
                break;
            default:
                break;
        }
        node->setName(nodeType->name());
    }
}

btNodeTypesModel::~btNodeTypesModel()
{
    delete(rootNode);
}

void btNodeTypesModel::newBehaviorTreeTypeAdded(btEditorNodeType* newType)
{
    btNodeTypesModelNode *node;
    QModelIndex parent;
    switch(newType->type())
    {
        case btNodeType::ActionNodeType:
            node = new btNodeTypesModelNode(newType, nodeAction);
            parent = createIndex(nodeAction->row(), 0, node);
            break;
        case btNodeType::ConditionNodeType:
            node = new btNodeTypesModelNode(newType, nodeCondition);
            parent = createIndex(nodeCondition->row(), 0, node);
            break;
        case btNodeType::CompositeNodeType:
            node = new btNodeTypesModelNode(newType, nodeComposite);
            parent = createIndex(nodeComposite->row(), 0, node);
            break;
        case btNodeType::DecoratorNodeType:
            node = new btNodeTypesModelNode(newType, nodeDecorator);
            parent = createIndex(nodeDecorator->row(), 0, node);
            break;
        case btNodeType::ReferenceNodeType:
            node = new btNodeTypesModelNode(newType, nodeReference);
            parent = createIndex(nodeReference->row(), 0, node);
            break;
        default:
            break;
    }
    node->setName(newType->name());
    dataChanged(parent, parent);
}

QVariant btNodeTypesModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
        return rootNode->data(section);

    return QVariant();
}

QVariant btNodeTypesModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (role != Qt::DisplayRole)
        return QVariant();

    btNodeTypesModelNode *node = static_cast<btNodeTypesModelNode*>(index.internalPointer());

    return node->data(index.column());
}

Qt::ItemFlags btNodeTypesModel::flags(const QModelIndex &index) const
{
    Qt::ItemFlags defaultFlags = QAbstractItemModel::flags(index);
    Qt::ItemFlags thisIndexFlags;
    
    if (index.isValid())
    {
        btNodeTypesModelNode *node = static_cast<btNodeTypesModelNode*>(index.internalPointer());
        if(node->nodeType())
            thisIndexFlags = Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsDragEnabled | Qt::ItemIsDropEnabled | defaultFlags;
        else
            thisIndexFlags = Qt::ItemIsEnabled | Qt::ItemIsDropEnabled | defaultFlags;
    }
    else
        thisIndexFlags = Qt::ItemIsEnabled | Qt::ItemIsDropEnabled | defaultFlags;
    
    return thisIndexFlags;
}

QModelIndex btNodeTypesModel::index(int row, int column, const QModelIndex &parent) const
{
    btNodeTypesModelNode *parentNode;
    
    if(!parent.isValid())
        parentNode = rootNode;
    else
        parentNode = static_cast<btNodeTypesModelNode*>(parent.internalPointer());

    btNodeTypesModelNode *childNode = parentNode->child(row);
    if(childNode)
        return createIndex(row, column, childNode);
    else
        return QModelIndex();
}

QModelIndex btNodeTypesModel::parent(const QModelIndex &child) const
{
    if(!child.isValid())
        return QModelIndex();

    btNodeTypesModelNode *childNode = static_cast<btNodeTypesModelNode*>(child.internalPointer());
    btNodeTypesModelNode *parentNode = childNode->parent();

	if(!parentNode)
		return QModelIndex();
	
    if (parentNode == rootNode)
        return QModelIndex();

    return createIndex(parentNode->row(), 0, parentNode);
}

int btNodeTypesModel::rowCount(const QModelIndex &index) const
{
    btNodeTypesModelNode *node;

    if (!index.isValid())
        node = rootNode;
    else
        node = static_cast<btNodeTypesModelNode*>(index.internalPointer());

    return node->childCount();
}

int btNodeTypesModel::columnCount(const QModelIndex &index) const
{
    if (index.isValid())
        return static_cast<btNodeTypesModelNode*>(index.internalPointer())->columnCount();
    else
        return rootNode->columnCount();
}

btEditorNodeType *btNodeTypesModel::nodeTypeFromIndex(const QModelIndex &index) const
{
    /*if(index.isValid())
        return static_cast<btNodeType*>(nodeTypes.at(index.row()));
    else*/
        return 0;
}

Qt::DropActions btNodeTypesModel::supportedDropActions() const
{
    return Qt::CopyAction;
}

QStringList btNodeTypesModel::mimeTypes() const
{
    QStringList types;
    types << "application/bt.nodetype";
    return types;
}

QMimeData* btNodeTypesModel::mimeData(const QModelIndexList &indexes) const
{
    QMimeData *mimeData = new QMimeData();
    QByteArray encodedData;
    QDataStream stream(&encodedData, QIODevice::WriteOnly);
    
    foreach(QModelIndex index, indexes)
    {
        if (index.isValid())
        {
            btNodeTypesModelNode *node = static_cast<btNodeTypesModelNode*>(index.internalPointer());
            if(node->nodeType())
            {
                stream << node->name();
                stream << node->nodeType()->name();
            }
        }
    }
    mimeData->setData("application/bt.nodetype", encodedData);
    return mimeData;
}

#include "btnodetypesmodel.moc"
