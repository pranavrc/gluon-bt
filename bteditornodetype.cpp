#include "bteditornodetype.h"

#include "projectparser.h"
#include "nodetypefactory.h"

btEditorNodeType::btEditorNodeType()
{
}

btEditorNodeType * btEditorNodeType::copy()
{
    btEditorNodeType * copyNode = nodeTypeFactory::instance()->newObject(this->type());
    
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

const QString btEditorNodeType::toNodeTypeXml()
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

const QString btEditorNodeType::toDataXml()
{
    return "";
}

#include "bteditornodetype.moc"