#include <QString>
#include <QVariant>
#include "btnode.h"
#include "btnodetype.h"
#include <QtCore/QDebug>
btNode::btNode(btNodeType *type, btNode *parent) : QObject(parent)
{
	this->m_type = type;
	this->parentNode = parent;
	if(parent)
		parent->appendChild(this);
}

btNode::~btNode()
{
    qDeleteAll(m_children);
    qDeleteAll(m_decorators);
}

bool btNode::runBehavior()
{    
    for (int i = 0; i < m_decorators.size(); i++)
    {
        qDebug() << m_decorators[i]->className();
        if (!m_decorators[i]->run()) 
        {
            return false;
        }
    }
    
    if(m_type)
    {
        if(!m_type->run())
        {
            return false;
        }
    }
    
    return true;
}

void btNode::appendChild(btNode *node)
{
    m_children.append(node);
    //has to be in the list, before this function is called
    m_type->appendingChild(m_children.count()-1);
    node->setParentNode(this);
}

void btNode::removeChild(int row)
{
    //has to be removed from the list before it is removed from the m_children list
    m_type->removingChild(row);
    m_children.removeAt(row);
}

btNode *btNode::child(int row)
{
    return m_children.value(row);
}

int btNode::childCount() const
{
    return m_children.count();
}

int btNode::columnCount() const
{
	return 3;
}

int btNode::row() const
{
	if(parentNode)
        return parentNode->m_children.indexOf(const_cast<btNode *>(this));
	
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
    
    return QVariant();
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

void btNode::addDecorator(btNodeType* decorator) 
{
    m_decorators.append(decorator); 
    decorator->setParentNode(this);
}
void btNode::removeDecorator(btNodeType* decorator) { m_decorators.removeAll(decorator); }
int btNode::decoratorCount() { return m_decorators.count(); }
QList<btNodeType*> btNode::decorators() const { return m_decorators; }

void btNode::setParentNode(btNode* node)
{
    parentNode = node;
    this->setParent(node);
}

void btNode::doneParsingChildren()
{
    m_type->childrenAdded();
}

#include "btnode.moc"
