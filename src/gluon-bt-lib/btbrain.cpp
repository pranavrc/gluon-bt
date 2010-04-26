#include "btbrain.h"

#include "btnode.h"
#include "btfactory.h"

#include <QtCore/QDebug>

btBrain::btBrain(QString data, QString file)
{
	m_file = file;
	
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
        parseBehaviorTrees(behaviorTrees, NULL, 0);
    }
}

btBrain::~btBrain()
{
	qDeleteAll(m_behaviorTrees.values());
	m_behaviorTrees.clear();
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

void btBrain::parseBehaviorTrees(QDomNode xNode, btNode * node, int nodeIndex)
{    
	btNode * workingBtNode = node;
    
    for(int i = 0; i < xNode.childNodes().count(); i++)
    {
        QDomNode currentNode = xNode.childNodes().at(i);
        QDomNamedNodeMap nodeAttributes = currentNode.attributes();
        
        if(!nodeAttributes.namedItem("uid").isNull())
        {
            btNode* rootNode = m_behaviorTrees[nodeAttributes.namedItem("uid").nodeValue().toInt()];
            parseBehaviorTrees(currentNode, rootNode, 0);            
        }
        else
        {            
            if(currentNode.nodeName() == "property")
            {
                btFactory::instance()->addProperty(workingBtNode, currentNode, this);
                continue;
            }
            
            if(currentNode.nodeName() == "decorator")
            {                
                if(workingBtNode == node->parentNode())
                {
                    btNode * child = workingBtNode->child(workingBtNode->childCount()-1);
                    workingBtNode->removeChild(child);
                    workingBtNode->insertChild(nodeIndex, child);
                    workingBtNode = child;
					
                }
                else if(workingBtNode->type() == btNode::DecoratorNodeType)
                {
                    workingBtNode = workingBtNode->child(0);
                }
                else
                {
                    workingBtNode = node->parentNode();
                    workingBtNode->removeChild(nodeIndex);
                }
            }
            else if(workingBtNode->type() == btNode::DecoratorNodeType) 
            {
                if(workingBtNode->childCount() > 0 && workingBtNode->child(0)->type() == btNode::DecoratorNodeType)
                {
                    workingBtNode = workingBtNode->child(0);
                }
                
                workingBtNode->appendChild(node);
                workingBtNode = node;
            }
            else if(workingBtNode->childCount() > 0 && workingBtNode->child(workingBtNode->childCount()-1)->type() == btNode::DecoratorNodeType)
            {
                workingBtNode->child(workingBtNode->childCount()-1)->appendChild(node);
                workingBtNode = node;
            }
			
            btNode *  newBTNode = btFactory::instance()->newObject(currentNode, workingBtNode ,this);

            if(newBTNode != NULL)
            {
                if(currentNode.hasChildNodes())
                {
                    parseBehaviorTrees(currentNode, newBTNode, i);
                }
                
                newBTNode->doneParsingChildren();
            }
        }
    }
}

QList<btPerceptionInfo*> btBrain::perceptionInfos() const
{
	return m_perceptionInfos;
}

void btBrain::setPerceptionInfos(const QList<btPerceptionInfo*>& newPerceptionInfos)
{
	m_perceptionInfos = newPerceptionInfos;
}

btPerceptionInfo* btBrain::perceptionInfo(const QString& name) const
{
	foreach(btPerceptionInfo * info, m_perceptionInfos)
	{
		if(info->objectName() == name)
		{
			return info;
		}
	}
	
	return NULL;
}

void btBrain::addPerceptionInfo(btPerceptionInfo * newPercpetionInfo)
{
	m_perceptionInfos.append(newPercpetionInfo);
}

QString btBrain::getFile()
{
	return m_file;
}

#include "btbrain.moc"

