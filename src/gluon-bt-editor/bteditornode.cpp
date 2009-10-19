#include "bteditornode.h"

#include "bttreemodel.h"
#include "projectparser.h"
#include "btreferencenode.h"

btEditorNode::btEditorNode(btNodeType *type, btNode *parent) : btNode(type, parent)
{
}

const QString btEditorNode::toXml(QList<btTreeModel *> behaviorTrees)
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
                properties += QVariant(i).toString();
            }
        }
        properties += "\" />";
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
    
    for(int i = 0; i < this->decoratorCount(); i++)
    {
        children += qobject_cast<btEditorNodeType*>( this->decorators().at(i))->toDataXml();
    }
    
    for(int i = 0; i < this->childCount(); i++)
    {
        children += qobject_cast<btEditorNode*>(this->child(i))->toXml(behaviorTrees);
    }
    projectParser::instance()->decreaseIndents();
    
    return startTag + properties + children + endTag;
}

#include "bteditornode.moc"