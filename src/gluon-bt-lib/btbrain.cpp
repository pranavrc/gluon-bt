#include "btbrain.h"

#include "btnode.h"
#include "btfactory.h"

#include <QtCore/QDebug>

btBrain::btBrain(QString data)
{
    QDomDocument xmlDocument("data");
    if(xmlDocument.setContent(data))
    {
        QDomElement rootNode = xmlDocument.documentElement();
        QDomNamedNodeMap rootNodeAttributes = rootNode.attributes();
    
        this->setName(rootNodeAttributes.namedItem("name").nodeValue());
    
        QDomNode nodeTypes = rootNode.namedItem("nodetypes");
        QDomNode behaviorTrees = rootNode.namedItem("behaviortrees");
        
        parseNodeTypes(nodeTypes);
        
        for(int i = 0; i < behaviorTrees.childNodes().count(); i++)
        {
            QDomNode currentNode = behaviorTrees.childNodes().at(i);
            QDomNamedNodeMap nodeAttributes = currentNode.attributes();
            
            btNode * newRootNode = btFactory::instance()->createRootNode(currentNode, this);            
            m_behaviorTrees[nodeAttributes.namedItem("uid").nodeValue().toInt()] = newRootNode;
        }
        
        //then parse every tree, and link them together
        parseBehaviorTrees(behaviorTrees, NULL);
    }
}

btBrain::~btBrain()
{
}

btNode* btBrain::getBehaviorTree(int index)
{
    if(m_behaviorTrees.contains(index)){
        return m_behaviorTrees[index];
    }
    return NULL;
}


int btBrain::behaviorTreesCount()
{
    return m_behaviorTrees.count();
}

    
QString btBrain::name()
{
    return m_name;
}

void btBrain::setName(QString name)
{
    m_name = name;
}

QString btBrain::description()
{
    return m_description;
}

void btBrain::setDescription(QString description)
{
    m_description = description;
}

void btBrain::parseNodeTypes(QDomNode xNode)
{
    for (int i = 0; i < xNode.childNodes().count(); i++)
    {
        btFactory::instance()->initNodeType(xNode.childNodes().at(i));
    }

}

void btBrain::parseBehaviorTrees(QDomNode xNode, btNode * node)
{    
    for(int i = 0; i < xNode.childNodes().count(); i++)
    {
        QDomNode currentNode = xNode.childNodes().at(i);
        QDomNamedNodeMap nodeAttributes = currentNode.attributes();
        
        if(!nodeAttributes.namedItem("uid").isNull())
        {
            btNode* rootNode = m_behaviorTrees[nodeAttributes.namedItem("uid").nodeValue().toInt()];
            parseBehaviorTrees(currentNode, rootNode);            
        }
        else
        {            
            if(currentNode.nodeName() == "property")
            {
                btFactory::instance()->addProperty(node, currentNode, this);
                continue;
            }
            
			btNode * newBTNode = NULL;
			
            if(currentNode.nodeName() == "decorator")
            {
				btNode* parentNode = node->parentNode();
				newBTNode = btFactory::instance()->newObject(currentNode, parentNode, this);
				newBTNode->appendChild(node);
				parentNode->removeChild(parentNode->childCount()-1);
				parentNode->appendChild(newBTNode);
				newBTNode = node;
			}
			else
			{
				newBTNode = btFactory::instance()->newObject(currentNode, node ,this);
			}
			
            if(newBTNode != NULL)
            {
                if(currentNode.hasChildNodes())
                {
                    parseBehaviorTrees(currentNode, newBTNode);
                }
				
				newBTNode->doneParsingChildren();
            }
        }
    }

}

#include "btbrain.moc"

