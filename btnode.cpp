#include <QString>
#include <QVariant>
#include "btnode.h"
#include "btnodetype.h"

btNode::btNode(btNodeType *type, btNode *parent)
{
	this->m_type = type;
	this->parentNode = parent;
	if(parent)
		parent->appendChild(this);
}

btNode::~btNode()
{
    qDeleteAll(children);
    delete(parentNode);
	// m_type is pointing to an entry in a list of items in btBrain, and as such should NOT be deleted here - the code is here to make clear exactly what not to write
    // delete(m_type);
}

void btNode::appendChild(btNode *node)
{
	children.append(node);
}

btNode *btNode::child(int row)
{
	return children.value(row);
}

int btNode::childCount() const
{
	return children.count();
}

int btNode::columnCount() const
{
	// This is name + description + whatever data the node type asks for
	return nodeData.count() + 2;
}

int btNode::row() const
{
	if(parentNode)
		return parentNode->children.indexOf(const_cast<btNode *>(this));
	
	return 0;
}

btNode *btNode::parent()
{
	return parentNode;
}

QVariant btNode::data(int column) const
{
	switch(column)
	{
		case 0:
            return name();
			break;
        case 1:
            if( decorators.count() > 0 )
                return QString("%1 (%2)").arg(description()).arg(decorators.count());
            else
                return description();
			break;
		default:
			return nodeData.value(column - 2);
			break;
	}
	return QVariant();
}

void btNode::setName(QString name) { m_name = name; }
QString btNode::name() const { return m_name; }

void btNode::setDescription(QString description) { m_description = description; }
QString btNode::description() const { return m_description; }

void btNode::setType(btNodeType *type) { m_type = type; }
btNodeType *btNode::type() const { return m_type; }

void btNode::addDecorator(btDecoratorNode* decorator) { decorators.append(decorator); }
void btNode::removeDecorator(btDecoratorNode* decorator) { decorators.removeAll(decorator); }
int btNode::decoratorCount() { return decorators.count(); }

