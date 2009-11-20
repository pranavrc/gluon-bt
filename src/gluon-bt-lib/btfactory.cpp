#include "btfactory.h"

#include "btnode.h"
#include "btnodetype.h"
#include "btbrain.h"
#include "btselectornode.h"
#include "btsequencenode.h"

#include <QtCore/QDebug>

btFactory::btFactory()
{
    m_nodeTypes["[selector]"] = new btSelectorNode();
    m_nodeTypes["[sequence]"] = new btSequenceNode();
}

btFactory* btFactory::instance()
{
    static btFactory* m_instance;
    
    if(m_instance == 0)
    {
        m_instance = new btFactory();
    }
    
    return m_instance;
}

btNode* btFactory::newObject(QDomNode xmlNode, btNode* parentNode, btBrain* brain)
{
    if(xmlNode.attributes().namedItem("nodetype").nodeValue() == "[reference]")
    {
        this->addProperty(parentNode, xmlNode.childNodes().at(0), brain);
        return NULL;
    }
    
    btNode* newBTNode = new btNode();
    
    btNodeType* nodeType = m_nodeTypes[xmlNode.attributes().namedItem("nodetype").nodeValue()];
    newBTNode->setType((btNodeType*)nodeType->metaObject()->newInstance());
    
    foreach(const QString &name ,nodeType->dynamicPropertyNames())
    {
        newBTNode->type()->setProperty(name.toUtf8(),nodeType->property(name.toUtf8()));
    }
    
    newBTNode->type()->setParentNode(newBTNode);
    
    if(!xmlNode.attributes().namedItem("name").isNull())
    {
        newBTNode->setName(xmlNode.attributes().namedItem("name").nodeValue());
    }
    if(!xmlNode.attributes().namedItem("description").isNull())
    {
        newBTNode->setDescription(xmlNode.attributes().namedItem("description").nodeValue());
    }
    
    if(xmlNode.nodeName() == "decorator")
    {
        parentNode->addDecorator(newBTNode->type());
        
        for(int i = 0; i < xmlNode.childNodes().count(); i++)
        {
            btFactory::instance()->addProperty(newBTNode, xmlNode.childNodes().at(i) , brain);
        }
        
        delete newBTNode;
        return NULL;
    }

    parentNode->appendChild(newBTNode);
    newBTNode->setParentNode(parentNode);
    
    return newBTNode;
}
                               
btNode* btFactory::newObject(QString className)
{
    btNode* newBTNode = new btNode();
    newBTNode->setType((btNodeType*)m_nodeTypes[className]->metaObject()->newInstance());
    newBTNode->type()->setParentNode(newBTNode);
    return newBTNode;
}
                               

void btFactory::registerNodeType(btNodeType* nodeType)
{
    m_nodeTypes[nodeType->metaObject()->className()] = nodeType;
}

btNodeType* btFactory::getRegisteredNodeType(QString className)
{
    return m_nodeTypes[className];
}

void btFactory::initNodeType(QDomNode xmlNode)
{
    QDomNamedNodeMap nodeTypeAttributes = xmlNode.attributes();
    btNodeType* nodeType = btFactory::instance()->getRegisteredNodeType(nodeTypeAttributes.namedItem("classname").nodeValue());
    nodeType->setName(nodeTypeAttributes.namedItem("name").nodeValue());
    nodeType->setDescription(nodeTypeAttributes.namedItem("description").nodeValue());
    nodeType->setClassName(nodeTypeAttributes.namedItem("classname").nodeValue());
    
    for(int j = 0; j < xmlNode.childNodes().count(); j++)
    {
        QDomNode currentProperty = xmlNode.childNodes().at(j);
        QDomNamedNodeMap propertyAttributes = currentProperty.attributes();
        nodeType->setProperty(propertyAttributes.namedItem("name").nodeValue().toUtf8(), propertyAttributes.namedItem("datatype").nodeValue());
    }    
    
}

void btFactory::addProperty(btNode* node, QDomNode xNode ,btBrain* brain)
{
    if(xNode.attributes().namedItem("name").nodeValue() == "reference")
    {
        node->appendChild(brain->getBehaviorTree(xNode.attributes().namedItem("value").nodeValue().toInt()));
        
        if(xNode.hasChildNodes())
        {
            for (int i = 0; i < xNode.childNodes().count(); i++) 
            {
                btFactory::instance()->newObject(xNode.childNodes().at(i), node, brain);
            }
        }
        
        return;
    }
    btNodeType* nodeType = node->type();
    
    
    int typeId = QMetaType::type(nodeType->property(xNode.attributes().namedItem("name").nodeValue().toUtf8()).toString().toUtf8());
    QVariant dataType;
    
    if(typeId == QVariant::List)
    {
        QVariantList list =  qvariant_cast<QVariantList>(QVariant((QVariant::Type)typeId));
        
        for(int i = 0; i < xNode.childNodes().count(); i++)
        {
            QDomNamedNodeMap attributes = xNode.childNodes().at(i).attributes();
            if(!attributes.namedItem("value").isNull())
                list.append(attributes.namedItem("value").nodeValue());
        }
        
        dataType = list;
    }
    else 
    {
        dataType = xNode.attributes().namedItem("value").nodeValue();
        dataType.convert((QVariant::Type)typeId);
    }
    
    
    nodeType->setProperty(xNode.attributes().namedItem("name").nodeValue().toUtf8(), dataType);
    
}

btNode* btFactory::createRootNode(QDomNode xmlNode, btBrain* brain)
{
    btNode* newRootNode = new btNode();
    newRootNode->setType((btNodeType*)this->m_nodeTypes["[sequence]"]->metaObject()->newInstance());
    newRootNode->type()->setParentNode(newRootNode);
    newRootNode->setParent(brain);
    
    newRootNode->setName(xmlNode.attributes().namedItem("name").nodeValue());
    newRootNode->setDescription(xmlNode.attributes().namedItem("description").nodeValue());
    
    return newRootNode;
}

#include "btfactory.moc"
