#include "projectparser.h"

#include <QDebug>
#include <QtXml>

#include "btbrain.h"
#include "btcompositenode.h"
#include "nodetypefactory.h"
#include "btnodetype.h"
#include "btnode.h"
#include "bttreemodel.h"
#include "btreferencenode.h"

projectParser::projectParser()
{
}

projectParser* projectParser::instance()
{
    static projectParser* projectParserInstance;
    if(projectParserInstance == 0)
    {
        projectParserInstance = new projectParser();
    }

    return projectParserInstance;
}

btBrain* projectParser::parseProject(QString xmlData)
{
    btBrain * brain = new btBrain();
    btCompositeNode * compositeNode = new btCompositeNode();
    compositeNode->setName("Selector");
    compositeNode->setDescription("A collection of behaviors which are launched in order, until one succeeds (only fails if all fails)");
    brain->nodeTypes.append(compositeNode);

    QDomDocument xmlDocument("data");
    if(xmlDocument.setContent(xmlData))
    {
        QDomElement rootNode = xmlDocument.documentElement();
        QDomNode nodeTypes = rootNode.namedItem("nodetypes");
        QDomNode behaviorTrees = rootNode.namedItem("behaviortrees");

        if(!nodeTypes.isNull())
        {
            parseNodeTypes(nodeTypes, brain);
        }

        if(!behaviorTrees.isNull())
        {
            //first parsing every root node of the behavior trees
            for(int i = 0; i < behaviorTrees.childNodes().count(); i++)
            {
                QDomNode currentNode = behaviorTrees.childNodes().at(i);
                QDomNamedNodeMap nodeAttributes = currentNode.attributes();

                btNode * newBTNode = new btNode();

                newBTNode->setType(nodeTypeFactory::instance()->newObject("composite"));

                btTreeModel* newTreeModel = new btTreeModel(brain, brain);
                newTreeModel->setRootNode(newBTNode);

                newTreeModel->setName(nodeAttributes.namedItem("name").nodeValue());
                newTreeModel->setDescription(nodeAttributes.namedItem("description").nodeValue());

                btReferenceNode* newTreeType = new btReferenceNode();
                newTreeType->setName(newTreeModel->name());
                newTreeType->setDescription(tr("A reference to the behavior tree named %1").arg(newTreeModel->name()));
                newTreeType->setReferenceBehaviorTree(newTreeModel);

                behaviorTreesList[nodeAttributes.namedItem("uid").nodeValue().toInt()] = newTreeModel;
                brain->addBehaviorTree(newTreeModel);
                brain->addNodeType(newTreeType);
            }

            //then parse every tree, and link them together
            parseBehaviorTrees(behaviorTrees, NULL,brain);
        }
    }

    return brain;
}

QString projectParser::serializeProject(btBrain * brain) const
{
    QString xmlData = "";

    return xmlData;
}

void projectParser::parseNodeTypes(QDomNode xNode, btBrain * brain)
{
    for (int i = 0; i < xNode.childNodes().count(); i++)
    {
        QDomNode currentNodeType = xNode.childNodes().at(i);
        QDomNamedNodeMap nodeTypeAttributes = currentNodeType.attributes();
        btNodeType* newNode = nodeTypeFactory::instance()->newObject(nodeTypeAttributes.namedItem("category").nodeValue());
        newNode->setName(nodeTypeAttributes.namedItem("name").nodeValue());
        newNode->setDescription(nodeTypeAttributes.namedItem("description").nodeValue());
<<<<<<< HEAD
        newNode->setClassName(nodeTypeAttributes.namedItem("classname").nodeValue());
=======
>>>>>>> files for parsing project files. Only nodetype parsing is working at the moment.

        for(int j = 0; j < currentNodeType.childNodes().count(); j++)
        {
            QDomNode currentProperty = currentNodeType.childNodes().at(j);
            QDomNamedNodeMap propertyAttributes = currentProperty.attributes();
            newNode->setProperty(propertyAttributes.namedItem("name").nodeName().toUtf8(), propertyAttributes.namedItem("name").nodeValue());
            newNode->setProperty(propertyAttributes.namedItem("description").nodeName().toUtf8(), propertyAttributes.namedItem("description").nodeValue());
            newNode->setProperty(propertyAttributes.namedItem("datatype").nodeName().toUtf8(), propertyAttributes.namedItem("datatype").nodeValue());
        }

<<<<<<< HEAD
        brain->addNodeType(newNode);
    }
}

void projectParser::parseBehaviorTrees(QDomNode xNode, btNode * node ,btBrain * brain)
{
    for(int i = 0; i < xNode.childNodes().count(); i++)
    {
        QDomNode currentNode = xNode.childNodes().at(i);
        QDomNamedNodeMap nodeAttributes = currentNode.attributes();

        if(!nodeAttributes.namedItem("uid").isNull())
        {
            btNode* rootNode = behaviorTreesList[nodeAttributes.namedItem("uid").nodeValue().toInt()]->rootNode();
            btNode* copyNode = new btNode( rootNode->type()->copy());
            copyNode->setName(rootNode->name());
            copyNode->setDescription(rootNode->description());

            parseBehaviorTrees(currentNode, copyNode, brain);

            behaviorTreesList[nodeAttributes.namedItem("uid").nodeValue().toInt()]->setRootNode(copyNode);
        }
        else
        {
            if(currentNode.nodeName() == "property")
            {
                btNodeType* nodeType = node->type()->copy();
                if(nodeAttributes.namedItem("name").nodeName() == "reference")
                {
                    btReferenceNode * btRefNode = qobject_cast<btReferenceNode*>(nodeType);
                    btRefNode->setReferenceBehaviorTree(behaviorTreesList[nodeAttributes.namedItem("value").nodeValue().toInt()]);
                }

                nodeType->setProperty(nodeAttributes.namedItem("name").nodeValue().toUtf8(), nodeAttributes.namedItem("value").nodeValue());
                node->setType(nodeType);
                return;
            }

            btNode *  newBTNode = new btNode();

            for(int j = 0; j < nodeAttributes.count(); j++)
            {
                QDomNode currentAttribute = nodeAttributes.item(j);
                qDebug() << "nodename" << currentAttribute.nodeName();
                qDebug() << "nodevalue" << currentAttribute.nodeValue();
                if(currentAttribute.nodeName() == "nodetype")
                {
                    for(int k = 0; k < brain->nodeTypes.count(); k++)
                    {
                        if(brain->nodeTypes[k]->className() == nodeAttributes.namedItem("nodetype").nodeValue())
                        {
                            newBTNode->setType(brain->nodeTypes[k]->copy());
                            break;
                        }
                        else if(nodeAttributes.namedItem("nodetype").nodeValue() == "[reference]")
                        {
                            newBTNode->setType(new btReferenceNode());
                            break;
                        }
                    }
                }
                else
                {
                    btNodeType * btType =  newBTNode->type()->copy();
                    btType->setProperty(currentAttribute.nodeName().toUtf8(), currentAttribute.nodeValue());
                    newBTNode->setType(btType);
                }
            }

            newBTNode->setName(newBTNode->type()->name());
            newBTNode->setDescription(newBTNode->type()->description());

            if(currentNode.hasChildNodes())
            {
                parseBehaviorTrees(currentNode, newBTNode, brain);
            }

            if(newBTNode->type()->type() == btNodeType::DecoratorNodeType)
            {
                node->addDecorator(qobject_cast<btDecoratorNode*>(newBTNode->type()));
            }
            else
            {
                node->appendChild(newBTNode);
            }
            newBTNode->setParent(node);
        }
    }
=======
        brain->nodeTypes.append(newNode);
    }
}

void projectParser::parseBehaviorTrees(QDomNode xNode, btBrain * brain)
{
>>>>>>> files for parsing project files. Only nodetype parsing is working at the moment.
}

#include "projectparser.moc"
