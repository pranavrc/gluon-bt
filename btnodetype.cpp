#include "btnodetype.h"

#include "nodetypefactory.h"

btNodeType::btNodeType(QObject * parent)
{
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
    btNodeType * copyNode = nodeTypeFactory::instance()->newObject(this->type());

    const QMetaObject * mo = this->metaObject();

    for(int i = 0; i < mo->propertyCount(); i++)
    {
        QMetaProperty moProperty = mo->property(i);
        QString propertyName = moProperty.name();

        if(propertyName == "objectName")
        {
            continue;
        }

        copyNode->setProperty(propertyName.toUtf8(), this->property(moProperty.name()));
    }

    for(int i = 0; i < this->dynamicPropertyNames().count(); i++)
    {
        QString propertyName(this->dynamicPropertyNames().at(i));
        copyNode->setProperty(propertyName.toUtf8(), this->property(propertyName.toUtf8()));
    }

    return copyNode;
}

void btNodeType::setClassName(QString className)
{
    m_className = className;
}

QString btNodeType::className() const
{
    return m_className;
}

QString btNodeType::toXml()
{
    return "Hello";
}

#include "btnodetype.moc"
