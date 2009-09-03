#include "btnodetype.h"
#include "btnodetypesmodelnode.h"
#include "btnodetypesmodel.h"
#include "btbrain.h"

btNodeTypesModel::btNodeTypesModel(btBrain *brain, QObject* parent)
        :QAbstractItemModel(parent)
{
    rootNode = new btNodeTypesModelNode();
    rootNode->setName("Root node");

    nodeAction = new btNodeTypesModelNode();
    nodeAction->setName(tr("Action"));
    rootNode->appendChild(nodeAction);

    nodeCondition = new btNodeTypesModelNode();
    nodeCondition->setName(tr("Condition"));
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
        switch(nodeType->category())
        {
            case btNodeType::Action:
                node = new btNodeTypesModelNode(nodeType, nodeAction);
                break;
            case btNodeType::Condition:
                node = new btNodeTypesModelNode(nodeType, nodeCondition);
                break;
            case btNodeType::Composite:
                node = new btNodeTypesModelNode(nodeType, nodeComposite);
                break;
            case btNodeType::Decorator:
                node = new btNodeTypesModelNode(nodeType, nodeDecorator);
                break;
            case btNodeType::Reference:
                node = new btNodeTypesModelNode(nodeType, nodeReference);
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

void btNodeTypesModel::newBehaviorTreeTypeAdded(btNodeType* newType)
{
    btNodeTypesModelNode *node;
    switch(newType->category())
    {
        case btNodeType::Action:
            node = new btNodeTypesModelNode(newType, nodeAction);
            break;
        case btNodeType::Condition:
            node = new btNodeTypesModelNode(newType, nodeCondition);
            break;
        case btNodeType::Composite:
            node = new btNodeTypesModelNode(newType, nodeComposite);
            break;
        case btNodeType::Decorator:
            node = new btNodeTypesModelNode(newType, nodeDecorator);
            break;
        case btNodeType::Reference:
            node = new btNodeTypesModelNode(newType, nodeReference);
            break;
        default:
            break;
    }
    node->setName(newType->name());
    QModelIndex index = createIndex(node->row(), 0, node);
    this->dataChanged(index, index);
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
    if (!index.isValid())
        return Qt::ItemIsEnabled;

    return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
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

btNodeType *btNodeTypesModel::nodeTypeFromIndex(const QModelIndex &index) const
{
    /*if(index.isValid())
        return static_cast<btNodeType*>(nodeTypes.at(index.row()));
    else*/
        return 0;
}

#include "btnodetypesmodel.moc"
