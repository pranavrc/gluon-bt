#include "btnodetype.h"

btNodeType::btNodeType(QObject * parent)
{
    m_name = "";
}

btNodeType::~btNodeType()
{
}

void btNodeType::setName(QString name) { m_name = name; }
QString btNodeType::name() const { return m_name; }

void btNodeType::setDescription(QString description) { m_description = description; }
QString btNodeType::description() const { return m_description; }

void btNodeType::setNodeType(nodeType type){m_type = type;}
btNodeType::nodeType btNodeType::type() const
{
    if(m_type)
        return m_type;
    else
        return UnusableNodeType;
}

bool btNodeType::run()
{
    return false;
}

btNodeType * btNodeType::copy()
{
    return NULL;
}

void btNodeType::setClassName(QString className)
{
    m_className = className;
}

QString btNodeType::className() const
{
    return m_className;
}

void btNodeType::setParentNode(btNode* node)
{
    m_parent = node;
    this->setParent(node);
}

btNode* btNodeType::parentNode()
{
    return m_parent;
}

void btNodeType::setNodeProperty(QString propertyName, QString value)
{
    if(m_properties.contains(propertyName))
    {
        m_properties[propertyName].value = value;
    }
    else 
    {
#warning fix setting the description
        m_properties[propertyName].value = value;
        m_properties[propertyName].description = "";
    }
}

void btNodeType::removeNodeProperty(QString propertyName)
{
    m_properties.remove(propertyName);
}

QVariant btNodeType::getNodePropertyValue(QString propertyName)
{
    return m_properties[propertyName].value;
}

QString btNodeType::getNodePropertyDescription(QString propertyName)
{
    return m_properties[propertyName].description;
}

int btNodeType::nodePropertyCount()
{
    return m_properties.count();
}

#include "btnodetype.moc"
