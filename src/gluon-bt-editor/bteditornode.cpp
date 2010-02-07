#include "bteditornode.h"

#include "bttreemodel.h"
#include "projectparser.h"
#include "btreferencenode.h"
#include <QtCore/QDebug>
#include "btdecoratornode.h"
#include "btglobal.h"

#include <QtXml>

btEditorNode::btEditorNode(btNodeType *type, btNode *parent) : btNode(type, parent)
{
}

btEditorNode::~btEditorNode()
{
   qDeleteAll(m_decorators);
}

void btEditorNode::toXml(QXmlStreamWriter* xmlWriter, QList<btTreeModel *> behaviorTrees)
{
    qRegisterMetaType<btChildWeights>("btChildWeights");
    
	//QString startTag = projectParser::instance()->writeIndents() + "<behaviornode ";
	xmlWriter->writeStartElement("behaviornode");

	
    //QString endTag = projectParser::instance()->writeIndents()+ "</behaviornode>";
    
	/*QString properties = "";
    QString children = "";
    
    startTag += "name=\"" + this->name() + "\" ";
    startTag += "description=\"" + this->description() + "\" ";*/
	xmlWriter->writeAttribute("name", this->name());
	xmlWriter->writeAttribute("description", this->description());
    
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
                //startTag += "nodetype=\"[reference]\" ";
				xmlWriter->writeAttribute("nodetype", "[reference]");
            }
            else
            {
				xmlWriter->writeAttribute("nodetype", nodeType->property(moProperty.name()).toString());
                //startTag += "nodetype=\"" + nodeType->property(moProperty.name()).toString() + "\" ";
            }
        }
    }
    
    //startTag += ">";
    
    //projectParser::instance()->increaseIndents();
    if(nodeType->type() == btNodeType::ReferenceNodeType)
    {
        btReferenceNode * btRefNode = qobject_cast<btReferenceNode*>(nodeType);
        //properties = projectParser::instance()->writeIndents() + "<property name=\"reference\" value=\"";
		xmlWriter->writeStartElement("property");
		xmlWriter->writeAttribute("name", "reference");
        
        for(int i = 0; i < behaviorTrees.count(); i ++)
        {
            if(btRefNode->referenceBehaviorTree() == behaviorTrees.at(i))
            {
                //properties += QVariant(i).toString();
				xmlWriter->writeAttribute("value",  QVariant(i).toString());
            }
        }
        
        if(this->decoratorCount() > 0)
        {
            
            /*properties += "\">";
            projectParser::instance()->increaseIndents();*/
            
            foreach(btNodeType* node, this->decorators())
            {
                btDecoratorNode* decorator = qobject_cast<btDecoratorNode*>(node);
                //properties += decorator->toDataXml();
				decorator->toDataXml(xmlWriter);
            }
            /*projectParser::instance()->decreaseIndents();
            properties += projectParser::instance()->writeIndents() + "</property>";*/
        }
        /*else
        {
            properties += "\" />";
        }*/
        
		xmlWriter->writeEndElement(); //property
        //return startTag + properties + children + endTag;
    }
    else
    {
        for(int i = 0; i < nodeType->dynamicPropertyNames().count(); i++)
        {
            QString propertyName(nodeType->dynamicPropertyNames().at(i));
            
            //properties += projectParser::instance()->writeIndents();
            //properties += "<property name=\"" + propertyName + "\" value=\"";
			xmlWriter->writeStartElement("property");
            
            QVariant value = nodeType->property(propertyName.toUtf8());
            
            if(value.type() == QVariant::List)
            {
                //properties += "\">";
                QVariantList list = qvariant_cast<QVariantList>(value);
                //projectParser::instance()->increaseIndents();
                
                foreach(const QVariant &v, list)
                {
					xmlWriter->writeStartElement("item");
					
					xmlWriter->writeAttribute("value", v.toString());
					
					xmlWriter->writeEndElement(); //item
                    //properties += projectParser::instance()->writeIndents() + "<item value=\"" + v.toString() + "\"/>";
                }
                    
                //projectParser::instance()->decreaseIndents();
                
                //properties += projectParser::instance()->writeIndents() + "</property>";
                
            }
            else if(value.type() == QVariant::UserType)
            {
                //properties += "\">";
                
                double totalProbability = 0.0;
                
                btChildWeights list = value.value<btChildWeights>();
                
                //projectParser::instance()->increaseIndents();
                
                foreach(const QVariant &v, list.childWeightList)
                {
                    totalProbability += v.toDouble();
                }
                
                foreach(const QVariant &v, list.childWeightList)
                {
                    QVariant prob = v.toDouble()/totalProbability;
					
					xmlWriter->writeStartElement("item");
					
					xmlWriter->writeAttribute("value", prob.toString());
					xmlWriter->writeAttribute("editorvalue", v.toString());
					
					xmlWriter->writeEndElement(); //item
                    //properties += projectParser::instance()->writeIndents() + "<item value=\"" + prob.toString() + "\"";
                    //properties += " editorvalue=\"" + v.toString()  + "\"/>";
                }
                
                //projectParser::instance()->decreaseIndents();
                
                //properties += projectParser::instance()->writeIndents() + "</property>";
            }
            /*else
            {                    
                properties +=  value.toString();
                properties += "\" />";
                
            }*/
			
			xmlWriter->writeEndElement(); //property
        }
    }
    
    for(int i = 0; i < this->decoratorCount(); i++)
    {
        //children += qobject_cast<btEditorNodeType*>(this->decorators().at(i))->toDataXml();
		qobject_cast<btEditorNodeType*>(this->decorators().at(i))->toDataXml(xmlWriter);
    }
    for(int i = 0; i < this->childCount(); i++)
    {
        //children += qobject_cast<btEditorNode*>(this->child(i))->toXml(behaviorTrees);
		qobject_cast<btEditorNode*>(this->child(i))->toXml(xmlWriter, behaviorTrees);
    }
    
    //projectParser::instance()->decreaseIndents();
    
    //return startTag + properties + children + endTag;
	
	xmlWriter->writeEndElement(); //behaviornode
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

void btEditorNode::addDecorator(btNodeType* decorator) 
{
    m_decorators.append(decorator); 
    decorator->setParentNode(this);
}

void btEditorNode::moveDecorator(int move, btNodeType * decorator)
{
    if(m_decorators.indexOf(decorator) > -1)
    {
        int orgIndex = m_decorators.indexOf(decorator);
        m_decorators.removeAt(orgIndex);
        int index = orgIndex + move;
        if(index < 0)
        {
            m_decorators.insert(0, decorator);
        }
        else if(index > m_decorators.count()-1)
        {
            m_decorators.append(decorator);
        }
        else 
        {
            m_decorators.insert(index, decorator);
        }

    }
}

void btEditorNode::removeDecorator(btNodeType* decorator) { m_decorators.removeAll(decorator); }
int btEditorNode::decoratorCount() const { return m_decorators.count(); }
QList<btNodeType*> btEditorNode::decorators() const { return m_decorators; }

void btEditorNode::emitUpdatePropertyWidget()
{
    emit updatePropertyWidget(this);
}

#include "bteditornode.moc"