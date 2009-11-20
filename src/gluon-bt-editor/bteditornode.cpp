#include "bteditornode.h"

#include "bttreemodel.h"
#include "projectparser.h"
#include "btreferencenode.h"
#include <QtCore/QDebug>
#include "btdecoratornode.h"

btEditorNode::btEditorNode(btNodeType *type, btNode *parent) : btNode(type, parent)
{
}

const QString btEditorNode::toXml(QList<btTreeModel *> behaviorTrees)
{
	QString startTag = projectParser::instance()->writeIndents() + "<behaviornode ";
    QString endTag = projectParser::instance()->writeIndents()+ "</behaviornode>";
    QString properties = "";
    QString children = "";
    
    startTag += "name=\"" + this->name() + "\" ";
    startTag += "description=\"" + this->description() + "\" ";
    
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
        
        if(propertyName == "className")
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
        
        if(this->decoratorCount() > 0)
        {
            
            properties += "\">";
            projectParser::instance()->increaseIndents();
            
            foreach(btNodeType* node, this->decorators())
            {
                btDecoratorNode* decorator = qobject_cast<btDecoratorNode*>(node);
                properties += decorator->toDataXml();
            }
            projectParser::instance()->decreaseIndents();
            properties += projectParser::instance()->writeIndents() + "</property>";
        }
        else
        {
            properties += "\" />";
        }
        
        return startTag + properties + children + endTag;
    }
    else
    {
        for(int i = 0; i < nodeType->dynamicPropertyNames().count(); i++)
        {
            QString propertyName(nodeType->dynamicPropertyNames().at(i));
            properties += projectParser::instance()->writeIndents();
            properties += "<property name=\"" + propertyName + "\" value=\"";
            
            QVariant value = nodeType->property(propertyName.toUtf8());
            
            if(value.type() == QVariant::List)
            {
                properties += "\">";
                
                QVariantList list = qvariant_cast<QVariantList>(value);
                
                projectParser::instance()->increaseIndents();
                foreach(const QVariant &v, list)
                {
                    properties += projectParser::instance()->writeIndents() + "<item value=\"" + v.toString() + "\"/>";
                }
                projectParser::instance()->decreaseIndents();
                
                properties += projectParser::instance()->writeIndents() + "</property>";
            }
            else 
            {
                qDebug() << value;
                properties +=  value.toString();
                properties += "\" />";
            }
        }
    }
    
    for(int i = 0; i < this->decoratorCount(); i++)
    {
        children += qobject_cast<btEditorNodeType*>( this->decorators().at(i))->toDataXml();
        qDebug() << children;
    }
    for(int i = 0; i < this->childCount(); i++)
    {
        children += qobject_cast<btEditorNode*>(this->child(i))->toXml(behaviorTrees);
    }
    projectParser::instance()->decreaseIndents();
    
    return startTag + properties + children + endTag;
}

QVariant btEditorNode::headerData(int column) const
{
    if(column == 0)
        return tr("Name");
    else if(column == 1)
        return tr("Description");
    else if(column == 2)
        return tr("Type");
    
    return QVariant();
}

QVariant btEditorNode::data(int column) const
{
	switch(column)
	{
		case 0:
            return name();
			break;
        case 1:
            if( !this->decorators().isEmpty() )
                return QString("%1 (%2)").arg(description()).arg(decoratorCount());
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

#include "bteditornode.moc"