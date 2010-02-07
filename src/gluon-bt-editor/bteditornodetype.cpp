#include "bteditornodetype.h"

#include "btglobal.h"
#include "projectparser.h"
#include "nodetypefactory.h"
#include "bteditornode.h"

#include <QtCore/QDebug>
#include <QtXml>

btEditorNodeType::btEditorNodeType(QObject * parent) : btNodeType(parent)
{
    setNodeType(btNodeType::UnusableNodeType);
}

void btEditorNodeType::setChildType(nodeType type){m_childtype = type;}

btNodeType::nodeType btEditorNodeType::childType() const
{
    if(m_childtype)
        return m_childtype;
    else
        return UnusableNodeType;
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
    
    QHashIterator<QString, QString> i(getPropertyDescriptions());
    while (i.hasNext())
    {
        i.next();
        copyNode->setPropertyDescription(i.key(), i.value());
    }
    
    return copyNode;

}

void btEditorNodeType::toNodeTypeXml(QXmlStreamWriter* xmlWriter)
{
	if(this->type() == btNodeType::ReferenceNodeType)
		return;
	
	//QString startTag = projectParser::instance()->writeIndents() +  "<nodetype ";
	xmlWriter->writeStartElement("nodetype");
	
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
            //startTag += "name=\"" + this->property(moProperty.name()).toString() + "\" ";
			xmlWriter->writeAttribute("name", this->property(moProperty.name()).toString());
        }
        else if(propertyName == "description")
        {
            //startTag += "description=\"" + this->property(moProperty.name()).toString() + "\" ";
			xmlWriter->writeAttribute("description", this->property(moProperty.name()).toString());
        }
        else if(propertyName == "className")
        {
            //startTag += "classname=\"" + this->property(moProperty.name()).toString() + "\" ";
			xmlWriter->writeAttribute("className", this->property(moProperty.name()).toString());
        }
    }
    
    switch(this->type())
    {
        case btNodeType::ActionNodeType:
            //startTag += "category=\"action\">";
			xmlWriter->writeAttribute("category", "action");
            break;
        case btNodeType::CompositeNodeType:
            //startTag += "category=\"composite\">";
			xmlWriter->writeAttribute("category", "composite");
            break;
        case btNodeType::ConditionNodeType:
            //startTag += "category=\"condition\">";
			xmlWriter->writeAttribute("category", "condition");
            break;
        case btNodeType::DecoratorNodeType:
            //startTag += "category=\"decorator\">";
			xmlWriter->writeAttribute("category", "decorator");
            break;
        case btNodeType::UnusableNodeType:
            //startTag += "category=\"unusable\">";
			xmlWriter->writeAttribute("category", "unusable");
            break;
    }
    
    //QString properties = "";
    
    //projectParser::instance()->increaseIndents();
	
    for(int i = 0; i < this->dynamicPropertyNames().count(); i++)
    {
        QString propertyName(this->dynamicPropertyNames().at(i));
		
		xmlWriter->writeStartElement(propertyName);
		
		xmlWriter->writeAttribute("name", propertyName);
		xmlWriter->writeAttribute("description", this->getPropertyDescription(propertyName));
		xmlWriter->writeAttribute("datatype", this->property(propertyName.toUtf8()).toString());
		
		xmlWriter->writeEndElement();
        /*properties += projectParser::instance()->writeIndents();
        properties += "<property name=\"" + propertyName + "\" ";
        properties += "description=\""+ this->getPropertyDescription(propertyName) + "\" ";
        properties += "datatype=\"" +this->property(propertyName.toUtf8()).toString();
        properties += "\" />";*/
    }
    /*projectParser::instance()->decreaseIndents();
    
    return startTag + properties + endTag;*/
	
	xmlWriter->writeEndElement();
	//QString endTag = projectParser::instance()->writeIndents() + "</nodetype>";
}

void btEditorNodeType::toDataXml(QXmlStreamWriter* xmlWriter)
{
}

void btEditorNodeType::initProperties()
{
    qRegisterMetaType<btChildWeights>("btChildWeights");
    
    foreach(const QString &name, this->dynamicPropertyNames())
    {
        int typeId = QMetaType::type(this->property(name.toUtf8()).toString().toUtf8());
        QVariant dataType;
        switch (typeId) 
        {
            case QVariant::Int:
                dataType = 0;
                break;
            case QVariant::Double:
                dataType = 0.00;
                break;
            case QVariant::String:
                dataType = "";
                break;
            case QVariant::List:
                dataType = QVariant(QVariant::List);
                break;
            default:
                if(typeId == QMetaType::type("btChildWeights"))
                {
                    btChildWeights ch;
                    dataType.setValue(ch);
                    break;
                }
                dataType = QVariant(QVariant::Invalid);
                break;
        }
        this->setProperty(name.toUtf8(), dataType);
    }
}

void btEditorNodeType::appendingChild(int index)
{
    qRegisterMetaType<btChildWeights>("btChildWeights");
    
    foreach(const QString &name, this->dynamicPropertyNames())
    {
        if(this->property(name.toUtf8()).type() == QVariant::UserType)
        {
            btChildWeights list = this->property(name.toUtf8()).value<btChildWeights>();
            
            if(this->parentNode()->child(index)->type()->property("probability").isValid())
            {
                list.childWeightList.insert(index, this->parentNode()->child(index)->type()->property("probability").toDouble());
                this->parentNode()->child(index)->type()->setProperty("probability", QVariant::Invalid);
            }
            
            QVariant v;
            v.setValue(list);
            this->setProperty(name.toUtf8(), v);
            break;
        }
    }
}

void btEditorNodeType::removingChild(int index)
{
    qRegisterMetaType<btChildWeights>("btChildWeights");
    
    btEditorNodeType * childNodeType = qobject_cast<btEditorNodeType*>(this->parentNode()->child(index)->type());
    childNodeType->disconnectChangeProperty();
    foreach(const QString &name, this->dynamicPropertyNames())
    {
        if(this->property(name.toUtf8()).type() == QVariant::UserType)        
        {
            btChildWeights list = this->property(name.toUtf8()).value<btChildWeights>();
            list.childWeightList.removeAt(index);
            QVariant v;
            v.setValue(list);
            this->setProperty(name.toUtf8(), v);
            break;
        }
    }
}

void btEditorNodeType::changeProbability(double value)
{
    qRegisterMetaType<btChildWeights>("btChildWeights");
    
    foreach(const QString &name, this->parentNode()->parentNode()->type()->dynamicPropertyNames())
    {
        if(this->parentNode()->parentNode()->type()->property(name.toUtf8()).type() == QVariant::UserType)
        {
            btChildWeights list = this->parentNode()->parentNode()->type()->property(name.toUtf8()).value<btChildWeights>();
            list.childWeightList[this->parentNode()->parentNode()->children().indexOf(this->parentNode())] = value;
            QVariant v;
            v.setValue(list);
            this->parentNode()->parentNode()->type()->setProperty(name.toUtf8(), v);
            break;
        }
    }
}

void btEditorNodeType::changeProperty(QString propertyName, QVariant value)
{
    qRegisterMetaType<btChildWeights>("btChildWeights");
    
    int typeId = QMetaType::type(value.toString().toUtf8());
    QVariant dataType;
    switch (typeId) 
    {
        case QVariant::Int:
            dataType = 0;
            break;
        case QVariant::Double:
            dataType = 0.00;
            break;
        case QVariant::String:
            dataType = "";
            break;
        case QVariant::List:
            dataType = QVariant(QVariant::List);
            break;
        default:
            if(typeId == QMetaType::type("btChildWeights"))
            {
                btChildWeights ch;
                
                for (int i = 0; i < this->parentNode()->childCount(); i++) {
                    ch.childWeightList.append(0.5);
                }
                
                dataType.setValue(ch);
                break;
            }
            dataType = QVariant(QVariant::Invalid);
            break;
    }
    
    this->setProperty(propertyName.toUtf8(), dataType);
}

void btEditorNodeType::disconnectChangeProperty()
{
    disconnect(m_sender, SIGNAL(propertyChanged(QString, QVariant)), this, SLOT(changeProperty(QString, QVariant)));
    disconnect(m_sender, SIGNAL(propertyDescriptionChanged(QString, QString, QString)), this, SLOT(changePropertyDescription(QString,QString, QString)));
    disconnect(m_sender, SIGNAL(nameChanged(QString)), this, SLOT(changeName(QString)));
    disconnect(m_sender, SIGNAL(descriptionChanged(QString)), this, SLOT(changeDescription(QString)));
    disconnect(m_sender, SIGNAL(classNameChanged(QString)), this, SLOT(changeClassName(QString)));
}

void btEditorNodeType::connectChangeProperty(btEditorNodeType* sender)
{
    m_sender = sender;
    connect(m_sender, SIGNAL(propertyChanged(QString, QVariant)), this, SLOT(changeProperty(QString, QVariant)));
    connect(m_sender, SIGNAL(propertyDescriptionChanged(QString, QString, QString)), this, SLOT(changePropertyDescription(QString,QString, QString)));
    connect(m_sender, SIGNAL(nameChanged(QString)), this, SLOT(changeName(QString)));
    connect(m_sender, SIGNAL(descriptionChanged(QString)), this, SLOT(changeDescription(QString)));
    connect(m_sender, SIGNAL(classNameChanged(QString)), this, SLOT(changeClassName(QString)));
}

void btEditorNodeType::emitPropertyChangedSignal(QString propertyName, QVariant value)
{
    emit propertyChanged(propertyName, value);
}

void btEditorNodeType::emitPropertyDescriptionChangedSignal(QString propertyName, QString oldPropertyName , QString description)
{
    emit propertyDescriptionChanged(propertyName, oldPropertyName, description);
}

void btEditorNodeType::changePropertyDescription(QString propertyName, QString oldPropertyName , QString description)
{
    if(propertyName == "" && description == "")
    {
        removePropertyDescription(oldPropertyName);
    }
    else if(oldPropertyName == "")
    {
        setPropertyDescription(propertyName, description);
    }
    else
    {
        setPropertyDescription(propertyName, oldPropertyName, description);
    }
}

void btEditorNodeType::removeActionTriggered()
{        
    btEditorNode * node = qobject_cast<btEditorNode*>(parentNode());
    node->removeDecorator(this);
    node->emitUpdatePropertyWidget();
}

void btEditorNodeType::moveUpAction()
{    
    btEditorNode * node = qobject_cast<btEditorNode*>(parentNode());
    node->moveDecorator(-1, this);
    node->emitUpdatePropertyWidget();
}

void btEditorNodeType::moveDownAction()
{    
    btEditorNode * node = qobject_cast<btEditorNode*>(parentNode());
    node->moveDecorator(1, this);
    node->emitUpdatePropertyWidget();
}

void btEditorNodeType::emitNameChanged(QString name)
{
    emit nameChanged(name);
}

void btEditorNodeType::emitClassNameChanged(QString className)
{
    emit classNameChanged(className);
}

void btEditorNodeType::emitDescriptionChanged(QString description)
{
    emit descriptionChanged(description);
}

void btEditorNodeType::changeName(QString name)
{
    this->setName(name);
    emit nameChanged(name);
}

void btEditorNodeType::changeDescription(QString description)
{
    this->setDescription(description);
    emit descriptionChanged(description);
}

void btEditorNodeType::changeClassName(QString className)
{
    this->setClassName(className);
    emit classNameChanged(className);
}

#include "bteditornodetype.moc"
