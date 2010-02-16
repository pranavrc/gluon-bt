#include "btfactory.h"

#include "btnode.h"
#include "btbrain.h"
#include "btselectornode.h"
#include "btsequencenode.h"
#include "btreferencenode.h"
#include "btglobal.h"

#include <QtCore/QDebug>

btFactory::btFactory()
{
    m_nodeTypes["[selector]"] = new btSelectorNode();
    m_nodeTypes["[selector]"]->setType(btNode::CompositeNodeType);
    m_nodeTypes["[sequence]"] = new btSequenceNode();
    m_nodeTypes["[sequence]"]->setType(btNode::CompositeNodeType);
	m_nodeTypes["[reference]"] = new btReferenceNode();
	m_nodeTypes["[reference]"]->setType(btNode::ReferenceNodeType);
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
    
    //btNode* newBTNode = new btNode();
    
    //btNodeType* nodeType = m_nodeTypes[xmlNode.attributes().namedItem("nodetype").nodeValue()];
	btNode* nodeType = m_nodeTypes[xmlNode.attributes().namedItem("nodetype").nodeValue()];
	btNode* newBTNode = qobject_cast<btNode*>(nodeType->metaObject()->newInstance());
    //newBTNode->setType((btNodeType*)nodeType->metaObject()->newInstance());
    //newBTNode->type()->setNodeType(nodeType->type());
	newBTNode->setType(nodeType->type());
    
    foreach(const QString &name ,nodeType->dynamicPropertyNames())
    {
        newBTNode->setProperty(name.toUtf8(),nodeType->property(name.toUtf8()));
    }
    
    //newBTNode->type()->setParentNode(newBTNode);
    
    if(!xmlNode.attributes().namedItem("name").isNull())
    {
        newBTNode->setName(xmlNode.attributes().namedItem("name").nodeValue());
    }
    if(!xmlNode.attributes().namedItem("description").isNull())
    {
        newBTNode->setDescription(xmlNode.attributes().namedItem("description").nodeValue());
    }
    
    parentNode->appendChild(newBTNode);
    newBTNode->setParentNode(parentNode);
    
    return newBTNode;
}
                               
btNode* btFactory::newObject(QString className)
{
    //btNode* newBTNode = new btNode();
    //newBTNode->setType((btNodeType*)m_nodeTypes[className]->metaObject()->newInstance());
	btNode* newBTNode = qobject_cast<btNode*>(m_nodeTypes[className]->metaObject()->newInstance());
    //newBTNode->type()->setParentNode(newBTNode);
    return newBTNode;
}
                               

void btFactory::registerNodeType(btNode* nodeType)
{
    m_nodeTypes[nodeType->metaObject()->className()] = nodeType;
}

btNode* btFactory::getRegisteredNodeType(QString className)
{
    return m_nodeTypes[className];
}

void btFactory::initNodeType(QDomNode xmlNode)
{
    QDomNamedNodeMap nodeTypeAttributes = xmlNode.attributes();
    btNode* nodeType = btFactory::instance()->getRegisteredNodeType(nodeTypeAttributes.namedItem("className").nodeValue());
    nodeType->setName(nodeTypeAttributes.namedItem("name").nodeValue());
    nodeType->setDescription(nodeTypeAttributes.namedItem("description").nodeValue());
    nodeType->setClassName(nodeTypeAttributes.namedItem("className").nodeValue());
    
    QString typeCategory = nodeTypeAttributes.namedItem("category").nodeValue();
    
    if(typeCategory == "action")
    {
        nodeType->setType(btNode::ActionNodeType);
    }
    else if(typeCategory == "condition")
    {
        nodeType->setType(btNode::ConditionNodeType);
    }
    else if(typeCategory == "composite")
    {
        nodeType->setType(btNode::CompositeNodeType);
    }
    else if(typeCategory == "decorator")
    {
        nodeType->setType(btNode::DecoratorNodeType);
    }
    else if(typeCategory == "reference")
    {
        nodeType->setType(btNode::ReferenceNodeType);
    }
    else
    {
        nodeType->setType(btNode::UnusableNodeType);
    }
    
    for(int j = 0; j < xmlNode.childNodes().count(); j++)
    {
        QDomNode currentProperty = xmlNode.childNodes().at(j);
        QDomNamedNodeMap propertyAttributes = currentProperty.attributes();
        nodeType->setProperty(propertyAttributes.namedItem("name").nodeValue().toUtf8(), propertyAttributes.namedItem("datatype").nodeValue());
    }    
    
}

void btFactory::addProperty(btNode* node, QDomNode xNode ,btBrain* brain)
{
    qRegisterMetaType<btChildWeights>("btChildWeights");
    
    if(xNode.attributes().namedItem("name").nodeValue() == "reference")
    {
        btNode* currentParent = node;
        if(xNode.hasChildNodes())
        {
            for (int i = 0; i < xNode.childNodes().count(); i++)
            {
                currentParent = btFactory::instance()->newObject(xNode.childNodes().at(i), currentParent, brain);
            }
        }
        
		btReferenceNode * refNode = qobject_cast<btReferenceNode*>(btFactory::instance()->newObject("[reference]"));
		
		currentParent->appendChild(refNode);
		
		refNode->addParentNode(currentParent);
		refNode->appendChild(brain->getBehaviorTree(xNode.attributes().namedItem("value").nodeValue().toInt()));
		
        //currentParent->appendChild(brain->getBehaviorTree(xNode.attributes().namedItem("value").nodeValue().toInt()));
        
        return;
    }
    //btNodeType* nodeType = node->type();
    
    int typeId = QMetaType::type(node->property(xNode.attributes().namedItem("name").nodeValue().toUtf8()).toString().toUtf8());
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
    else if(typeId == QMetaType::type("btChildWeights"))
    {
        QVariantList list;
        
        for(int i = 0; i < xNode.childNodes().count(); i++)
        {
            QDomNamedNodeMap attributes = xNode.childNodes().at(i).attributes();
            if(!attributes.namedItem("value").isNull())
                list.append(attributes.namedItem("value").nodeValue().toDouble());
        }
        
        dataType = list;
    }
    else 
    {
        dataType = xNode.attributes().namedItem("value").nodeValue();
        dataType.convert((QVariant::Type)typeId);
    }
    
    node->setProperty(xNode.attributes().namedItem("name").nodeValue().toUtf8(), dataType);
    
}

btNode* btFactory::createRootNode(QDomNode xmlNode, btBrain* brain)
{
//    btNode* newRootNode = new btNode();
//    newRootNode->setType((btNodeType*)this->m_nodeTypes["[sequence]"]->metaObject()->newInstance());
	btNode* newRootNode = (btNode*)this->m_nodeTypes["[sequence]"]->metaObject()->newInstance();
    //newRootNode->type()->setParentNode(newRootNode);
    newRootNode->setParent(brain);
    
    newRootNode->setName(xmlNode.attributes().namedItem("name").nodeValue());
    newRootNode->setDescription(xmlNode.attributes().namedItem("description").nodeValue());
    
    return newRootNode;
}

#include "btfactory.moc"
