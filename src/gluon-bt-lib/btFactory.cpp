#include "btfactory.h"

#include "btnode.h"
#include "btnodetype.h"
#include "btbrain.h"

btFactory::btFactory()
{
    
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
    btNode* newBTNode = new btNode();
    
    if(!xmlNode.attributes().namedItem("nodetype").isNull() && !xmlNode.attributes().namedItem("nodetype").nodeValue().startsWith("["))
    {
        newBTNode->setType((btNodeType*)m_nodeTypes[xmlNode.attributes().namedItem("nodetype").nodeValue()]->metaObject()->newInstance());
        newBTNode->type()->setParent(newBTNode);
        
        for(int i = 0; i < xmlNode.attributes().count(); i++)
        {
            QDomNode currentAttribute = xmlNode.attributes().item(i);
            if(currentAttribute.nodeName() == "nodetype")
            {
                continue;
            }
         
            btNodeType * btType = newBTNode->type();
            btType->setProperty(currentAttribute.nodeName().toUtf8(), currentAttribute.nodeValue());
        }
        
        newBTNode->setName(newBTNode->type()->name());
        newBTNode->setDescription(newBTNode->type()->description());
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

#include "btfactory.moc"