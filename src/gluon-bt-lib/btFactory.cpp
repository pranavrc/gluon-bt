#include "btfactory.h"

#include "btnode.h"
#include "btnodetype.h"
#include "btbrain.h"
#include "btselectornode.h"
#include "btsequencenode.h"

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
    
    
    newBTNode->setType((btNodeType*)m_nodeTypes[xmlNode.attributes().namedItem("nodetype").nodeValue()]->metaObject()->newInstance());
    newBTNode->type()->setParent(newBTNode);
    
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
    newBTNode->type()->setParent(newBTNode);
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
    btNodeType* nodeType = btFactory::instance()->getRegisteredNodeType(nodeTypeAttributes.namedItem("className").nodeValue());
    nodeType->setName(nodeTypeAttributes.namedItem("name").nodeValue());
    nodeType->setDescription(nodeTypeAttributes.namedItem("description").nodeValue());
    nodeType->setClassName(nodeTypeAttributes.namedItem("classname").nodeValue());
    
    for(int j = 0; j < xmlNode.childNodes().count(); j++)
    {
        QDomNode currentProperty = xmlNode.childNodes().at(j);
        QDomNamedNodeMap propertyAttributes = currentProperty.attributes();
        /*newNode->setProperty(propertyAttributes.namedItem("name").nodeName().toUtf8(), propertyAttributes.namedItem("name").nodeValue());
         newNode->setProperty(propertyAttributes.namedItem("description").nodeName().toUtf8(), propertyAttributes.namedItem("description").nodeValue());
         newNode->setProperty(propertyAttributes.namedItem("datatype").nodeName().toUtf8(), propertyAttributes.namedItem("datatype").nodeValue());*/
        nodeType->setProperty(propertyAttributes.namedItem("name").nodeValue().toUtf8(), propertyAttributes.namedItem("datatype").nodeValue());
    }    
    
}

void btFactory::addProperty(btNode* node, QDomNode xNode ,btBrain* brain)
{
    if(xNode.attributes().namedItem("name").nodeValue() == "reference")
    {
        node->appendChild(brain->getBehaviorTree(xNode.attributes().namedItem("value").nodeValue().toInt()));
        return;
    }
    
    btNodeType* nodeType = node->type();
    nodeType->setProperty(xNode.attributes().namedItem("name").nodeValue().toUtf8(), xNode.attributes().namedItem("value").nodeValue());
    
}

btNode* btFactory::createRootNode(QDomNode xmlNode, btBrain* brain)
{
    btNode* newRootNode = new btNode();
    newRootNode->setType(this->m_nodeTypes["[sequence]"]);
    newRootNode->setParent(brain);
    
    newRootNode->setName(xmlNode.attributes().namedItem("name").nodeValue());
    newRootNode->setDescription(xmlNode.attributes().namedItem("description").nodeValue());
    
    return newRootNode;
}

#include "btfactory.moc"
