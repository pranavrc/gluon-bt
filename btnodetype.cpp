#include "btnodetype.h"

#include "nodetypefactory.h"
#include "projectparser.h"

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

const QString btNodeType::toNodeTypeXml()
{
	if(this->type() == btNodeType::ReferenceNodeType)
		return "";
	
    QString startTag = projectParser::instance()->writeIndents() +  "<nodetype ";
    QString endTag = projectParser::instance()->writeIndents() + "</nodetype>";

    const QMetaObject * mo = this->metaObject();

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
            startTag += "name=\"" + this->property(moProperty.name()).toString() + "\" ";
        }
        else if(propertyName == "description")
        {
            startTag += "description=\"" + this->property(moProperty.name()).toString() + "\" ";
        }
        else if(propertyName == "className")
        {
            startTag += "classname=\"" + this->property(moProperty.name()).toString() + "\" ";
        }
    }

    switch(this->type())
    {
    case btNodeType::ActionNodeType:
        startTag += "category=\"action\">";
        break;
    case btNodeType::CompositeNodeType:
        startTag += "category=\"composite\">";
        break;
    case btNodeType::ConditionNodeType:
        startTag += "category=\"condition\">";
        break;
    case btNodeType::DecoratorNodeType:
        startTag += "category=\"decorator\">";
        break;
    case btNodeType::UnusableNodeType:
        startTag += "category=\"unusable\">";
        break;
    }

    QString properties = "";

    projectParser::instance()->increaseIndents();
    for(int i = 0; i < this->dynamicPropertyNames().count(); i++)
    {
        QString propertyName(this->dynamicPropertyNames().at(i));
        properties += projectParser::instance()->writeIndents();
        properties += "<property name=\"" + propertyName + "\" description=\"\" datatype=\"";
        properties +=  this->property(propertyName.toUtf8()).toString();
        properties += "\" />";
    }
    projectParser::instance()->decreaseIndents();

    return startTag + properties + endTag;
}

const QString btNodeType::toDataXml()
{
    return "";
}

#include "btnodetype.moc"
