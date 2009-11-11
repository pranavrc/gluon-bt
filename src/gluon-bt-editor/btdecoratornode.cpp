#include "btdecoratornode.h"
#include "projectparser.h"

btDecoratorNode::btDecoratorNode()
{
    setNodeType(btNodeType::DecoratorNodeType);
}

btDecoratorNode::~btDecoratorNode()
{
}

bool btDecoratorNode::run()
{
	return false;
}

const QString btDecoratorNode::toDataXml()
{
    QString startTag = projectParser::instance()->writeIndents() + "<decorator ";
    QString endTag = projectParser::instance()->writeIndents() + "</decorator>";
    QString properties = "";
    
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
            startTag += "nodetype=\"" + this->property(moProperty.name()).toString() + "\" ";
        }
    }
    
    startTag += ">";
    
    projectParser::instance()->increaseIndents();
    for(int i = 0; i < this->dynamicPropertyNames().count(); i++)
    {
        QString propertyName(this->dynamicPropertyNames().at(i));
        properties += projectParser::instance()->writeIndents();
        properties += "<property name=\"" + propertyName + "\" value=\"";
        properties +=  this->property(propertyName.toUtf8()).toString();
        properties += "\" />";
    }
    projectParser::instance()->decreaseIndents();
    
    return startTag + properties + endTag;
}

#include "btdecoratornode.moc"
