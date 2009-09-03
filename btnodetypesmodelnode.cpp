#include "btnodetypesmodelnode.h"
#include "btnodetype.h"

btNodeTypesModelNode::btNodeTypesModelNode(btNodeType *data, btNodeTypesModelNode *parent)
{
    this->nodeData = data;
    this->parentNode = parent;
    if(parentNode)
        parentNode->appendChild(this);
}

btNodeTypesModelNode::~btNodeTypesModelNode()
{
    qDeleteAll(children);
}

void btNodeTypesModelNode::appendChild(btNodeTypesModelNode *child)
{
    children.append(child);
}

btNodeTypesModelNode *btNodeTypesModelNode::child(int row)
{
    return children.value(row);
}

int btNodeTypesModelNode::childCount() const
{
    return children.count();
}

int btNodeTypesModelNode::row() const
{
    if(parentNode)
        return parentNode->children.indexOf(const_cast<btNodeTypesModelNode*>(this));
    return 0;
}

int btNodeTypesModelNode::columnCount() const
{
    return 1;
}

QVariant btNodeTypesModelNode::data(int column) const
{
    Q_UNUSED(column);
    return m_name;
}

btNodeTypesModelNode *btNodeTypesModelNode::parent()
{
    return parentNode;
}

void btNodeTypesModelNode::setName(QString name) { m_name = name; }
QString btNodeTypesModelNode::name() const { return m_name; }
