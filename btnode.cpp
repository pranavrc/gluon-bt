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
    delete(m_type);
}

bool btNode::runBehavior()
{
    // First run all the decorators, and bail out if even one of them fails
    
    // Then run the behavior itself (that is, the btNodeType's run function)
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
	return 3;
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

QVariant btNode::headerData(int column) const
{
    if(column == 0)
        return tr("Name");
    else if(column == 1)
        return tr("Description");
    else if(column == 2)
        return tr("Type");
}

QVariant btNode::data(int column) const
{
	switch(column)
	{
		case 0:
            return name();
			break;
        case 1:
            if( !m_decorators.isEmpty() )
                return QString("%1 (%2)").arg(description()).arg(m_decorators.count());
            else
                return description();
			break;
        case 2:
            return type()->name();
            break;
		default:
			return QVariant();
			break;
	}
	return QVariant();
}

void btNode::setName(QString name) { m_name = name; }
QString btNode::name() const { return m_name; }

void btNode::setDescription(QString description) { m_description = description; }
QString btNode::description() const
{
    if(m_description.isEmpty())
        return type()->name();
    else
        return m_description;
}

void btNode::setType(btNodeType *type)
{
    delete(m_type);
    m_type = type;
}
btNodeType *btNode::type() const { return m_type; }

void btNode::addDecorator(btDecoratorNode* decorator) { m_decorators.append(decorator); }
void btNode::removeDecorator(btDecoratorNode* decorator) { m_decorators.removeAll(decorator); }
int btNode::decoratorCount() { return m_decorators.count(); }
QList<btDecoratorNode*> btNode::decorators() const { return m_decorators; }

void btNode::setParentNode(btNode * node)
{
    parentNode = node;
}

#include "btnode.moc"
