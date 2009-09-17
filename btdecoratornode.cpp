#include "btdecoratornode.h"

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

QString btDecoratorNode::toDataXml() const
{
    QString startTag = "<decorator ";
    QString endTag = "</decorator>";
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
            startTag += "classname=\"" + this->property(moProperty.name()).toString() + "\" ";
        }
    }
    
    startTag += ">";
    
    for(int i = 0; i < this->dynamicPropertyNames().count(); i++)
    {
        QString propertyName(this->dynamicPropertyNames().at(i));
        properties += "<property name=\"" + propertyName + "\" value=\"";
        properties +=  this->property(propertyName.toUtf8()).toString();
        properties += "\" />";
    }
    
    return startTag + properties + endTag;
}

#include "btdecoratornode.moc"