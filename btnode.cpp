#include <QString>
#include <QVariant>
#include "btnode.h"
#include "btnodetype.h"
#include "btreferencenode.h"
#include "bttreemodel.h"
#include "projectparser.h"

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
    //delete(m_type);
}

bool btNode::runBehavior()
{
    // First run all the decorators, and bail out if even one of them fails
    
    // Then run the behavior itself (that is, the btNodeType's run function)
}

void btNode::appendChild(btNode *node)
{
    m_children.append(node);
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

void btNode::setParentNode(btNode* node)
{
    delete(parentNode);
    parentNode = node;
    this->setParent(node);
}

const QString btNode::toXml(QList<btTreeModel *> behaviorTrees)
{
	QString startTag = projectParser::instance()->writeIndents() + "<behaviornode ";
    QString endTag = projectParser::instance()->writeIndents()+ "</behaviornode>";
    QString properties = "";
    QString children = "";
    btNodeType * nodeType = this->type();
    const QMetaObject * mo = nodeType->metaObject();
    
    for(int i = 0; i < mo->propertyCount(); i++)
    {
        QMetaProperty moProperty = mo->property(i);
        QString propertyName = moProperty.name();
        
        if(propertyName == "objectName")
        {
            continue;
        }
        
        if(propertyName == "name")
        {
            startTag += "name=\"" + nodeType->property(moProperty.name()).toString() + "\" ";
        }
        else if(propertyName == "description")
        {
            startTag += "description=\"" + nodeType->property(moProperty.name()).toString() + "\" ";
        }
        else if(propertyName == "className")
        {
            if(nodeType->type() == btNodeType::ReferenceNodeType)
            {
                startTag += "nodetype=\"[reference]\" ";
            }
            else
            {
                startTag += "nodetype=\"" + nodeType->property(moProperty.name()).toString() + "\" ";
            }
        }
    }
    
    startTag += ">";
    
    projectParser::instance()->increaseIndents();
    if(nodeType->type() == btNodeType::ReferenceNodeType)
    {
        btReferenceNode * btRefNode = qobject_cast<btReferenceNode*>(nodeType);
        properties = projectParser::instance()->writeIndents() + "<property name=\"reference\" value=\"";
        
        for(int i = 0; i < behaviorTrees.count(); i ++)
        {
            if(btRefNode->referenceBehaviorTree() == behaviorTrees.at(i))
            {
                properties += QVariant(i).toString() +"\" />";
            }
        }
    }
    else
    {
        for(int i = 0; i < nodeType->dynamicPropertyNames().count(); i++)
        {
            QString propertyName(nodeType->dynamicPropertyNames().at(i));
            properties += projectParser::instance()->writeIndents();
            properties += "<property name=\"" + propertyName + "\" value=\"";
            properties +=  nodeType->property(propertyName.toUtf8()).toString();
            properties += "\" />";
        }
    }
    
    for(int i = 0; i < this->m_decorators.count(); i++)
    {
        children += this->decorators().at(i)->toDataXml();
    }
    
    for(int i = 0; i < this->childCount(); i++)
    {
        children += m_children[i]->toXml(behaviorTrees);
    }
    projectParser::instance()->decreaseIndents();
    
    return startTag + properties + children + endTag;
}

#include "btnode.moc"
