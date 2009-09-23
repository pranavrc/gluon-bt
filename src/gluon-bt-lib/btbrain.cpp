#include "btbrain.h"

#include "btnode.h"
#include "btnodetype.h"
#include "btfactory.h"

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
            
            btNode * newRootNode = new btNode();
            newRootNode->setParent(this);
            
            newRootNode->setName(nodeAttributes.namedItem("name").nodeValue());
            newRootNode->setDescription(nodeAttributes.namedItem("description").nodeValue());
            
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
    return NULL;//m_behaviorTrees.at(index);
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
            
            btNode *  newBTNode = btFactory::instance()->newObject(currentNode, node ,this);
            
            if(newBTNode != NULL)
            {
                if(currentNode.hasChildNodes())
                {
                    parseBehaviorTrees(currentNode, newBTNode);
                }
            }
        }
    }

}

#include "btbrain.moc"
