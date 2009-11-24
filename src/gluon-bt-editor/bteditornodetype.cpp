#include "bteditornodetype.h"

#include "projectparser.h"
#include "nodetypefactory.h"

#include <QtCore/QDebug>

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
        properties += "<property name=\"" + propertyName + "\" ";
        properties += "description=\""+ this->getPropertyDescription(propertyName) + "\" ";
        properties += "datatype=\"" +this->property(propertyName.toUtf8()).toString();
        properties += "\" />";
    }
    projectParser::instance()->decreaseIndents();
    
    return startTag + properties + endTag;
}

const QString btEditorNodeType::toDataXml()
{
    return "";
}

void btEditorNodeType::initProperties()
{
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
                if(this->property(name.toUtf8()).toString() == "Child Weights")
                {
                    dataType = "[Child Weights]";
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
    if(!this->parentNode())
        return;
    
    foreach(const QString &name, this->dynamicPropertyNames())
    {
        if(this->property(name.toUtf8()) == "[Child Weights]" && !this->parentNode()->child(index)->type()->property("probability").isValid())
        {
            qDebug() << this->parentNode()->child(index)->type()->property("probability");
            this->parentNode()->child(index)->type()->setProperty("probability", 0.5);
            break;
        }
    }
}

void btEditorNodeType::removingChild(int index)
{
    btEditorNodeType * childNodeType = qobject_cast<btEditorNodeType*>(this->parentNode()->child(index)->type());
    childNodeType->setProperty("probability", QVariant());
    childNodeType->disconnectChangeProperty();
}

void btEditorNodeType::changeProbability(double value)
{
    this->setProperty("probability", value);
}

void btEditorNodeType::changeProperty(QString propertyName, QVariant value)
{
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
            qDebug() << value;
            if(value.toString() == "Child Weights")
            {
                dataType = "[Child Weights]";
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
}

void btEditorNodeType::connectChangeProperty(btEditorNodeType* sender)
{
    m_sender = sender;
    connect(m_sender, SIGNAL(propertyChanged(QString, QVariant)), this, SLOT(changeProperty(QString, QVariant)));
    connect(m_sender, SIGNAL(propertyDescriptionChanged(QString, QString, QString)), this, SLOT(changePropertyDescription(QString,QString, QString)));
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
    qDebug() << propertyName << " " << oldPropertyName << " " << description;
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

#include "bteditornodetype.moc"
