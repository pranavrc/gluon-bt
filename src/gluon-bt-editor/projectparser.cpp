#include "projectparser.h"

#include <QtXml>

#include "btbrain.h"
#include "btcompositenode.h"
#include "nodetypefactory.h"
#include "bteditornodetype.h"
#include "bteditornode.h"
#include "bttreemodel.h"
#include "btreferencenode.h"

projectParser::projectParser()
{
    m_indentCount = 0;
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

    QDomDocument xmlDocument("data");
    if(xmlDocument.setContent(xmlData))
    {
        QDomElement rootNode = xmlDocument.documentElement();
        QDomNamedNodeMap rootNodeAttributes = rootNode.attributes();
        
        brain->setName(rootNodeAttributes.namedItem("name").nodeValue());
        
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

                btEditorNode * newBTNode = new btEditorNode();

                newBTNode->setType(nodeTypeFactory::instance()->newObject("composite"));

                btTreeModel* newTreeModel = new btTreeModel(brain, brain);
                newTreeModel->setRootNode(newBTNode);

                newBTNode->setParent(newTreeModel);

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

void projectParser::parseNodeTypes(QDomNode xNode, btBrain * brain)
{
    for (int i = 0; i < xNode.childNodes().count(); i++)
    {
        QDomNode currentNodeType = xNode.childNodes().at(i);
        QDomNamedNodeMap nodeTypeAttributes = currentNodeType.attributes();
        btNodeType* newNode = nodeTypeFactory::instance()->newObject(nodeTypeAttributes.namedItem("category").nodeValue());
        newNode->setName(nodeTypeAttributes.namedItem("name").nodeValue());
        newNode->setDescription(nodeTypeAttributes.namedItem("description").nodeValue());
        newNode->setClassName(nodeTypeAttributes.namedItem("classname").nodeValue());

        for(int j = 0; j < currentNodeType.childNodes().count(); j++)
        {
            QDomNode currentProperty = currentNodeType.childNodes().at(j);
            QDomNamedNodeMap propertyAttributes = currentProperty.attributes();
            /*newNode->setProperty(propertyAttributes.namedItem("name").nodeName().toUtf8(), propertyAttributes.namedItem("name").nodeValue());
            newNode->setProperty(propertyAttributes.namedItem("description").nodeName().toUtf8(), propertyAttributes.namedItem("description").nodeValue());
            newNode->setProperty(propertyAttributes.namedItem("datatype").nodeName().toUtf8(), propertyAttributes.namedItem("datatype").nodeValue());*/
            newNode->setProperty(propertyAttributes.namedItem("name").nodeValue().toUtf8(), propertyAttributes.namedItem("datatype").nodeValue());
        }

        brain->addNodeType(qobject_cast<btEditorNodeType*>(newNode));
    }
}

void projectParser::parseBehaviorTrees(QDomNode xNode, btEditorNode * node ,btBrain * brain)
{
    for(int i = 0; i < xNode.childNodes().count(); i++)
    {
        QDomNode currentNode = xNode.childNodes().at(i);
        QDomNamedNodeMap nodeAttributes = currentNode.attributes();

        if(!nodeAttributes.namedItem("uid").isNull())
        {
            btEditorNode* rootNode = behaviorTreesList[nodeAttributes.namedItem("uid").nodeValue().toInt()]->rootNode();
            btEditorNode* copyNode = new btEditorNode( rootNode->type()->copy());
            copyNode->setParent(behaviorTreesList[nodeAttributes.namedItem("uid").nodeValue().toInt()]);
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
                if(nodeAttributes.namedItem("name").nodeValue() == "reference")
                {
                    btReferenceNode * btRefNode = qobject_cast<btReferenceNode*>(nodeType);
                    btRefNode->setReferenceBehaviorTree(behaviorTreesList[nodeAttributes.namedItem("value").nodeValue().toInt()]);
                }

                nodeType->setProperty(nodeAttributes.namedItem("name").nodeValue().toUtf8(), nodeAttributes.namedItem("value").nodeValue());
                node->setType(nodeType);
                continue;
            }

            btEditorNode *  newBTNode = new btEditorNode();

            qDebug() << nodeAttributes.count();
            
            for(int j = 0; j < nodeAttributes.count(); j++)
            {
                QDomNode currentAttribute = nodeAttributes.item(j);
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
                    btEditorNodeType * btType = qobject_cast<btEditorNodeType*>(newBTNode->type())->copy();
                    btType->setProperty(currentAttribute.nodeName().toUtf8(), currentAttribute.nodeValue());
                    newBTNode->setType(btType);
                }
            }

            newBTNode->setName(newBTNode->type()->name());
            newBTNode->setDescription(newBTNode->type()->description());
            qDebug() << newBTNode->name();
            qDebug() << newBTNode->description();

            if(currentNode.hasChildNodes())
            {
                parseBehaviorTrees(currentNode, newBTNode, brain);
            }

            if(newBTNode->type()->type() == btEditorNodeType::DecoratorNodeType)
            {
                node->addDecorator(qobject_cast<btDecoratorNode*>(newBTNode->type()));
            }
            else
            {
                node->appendChild(newBTNode);
            }
            newBTNode->setParentNode(node);
        }
    }
}

const QString projectParser::serializeProject(btBrain * brain)
{
    QString xmlData = "<?xml version=\"1.0\" encoding=\"UTF-8\" ?>";

    xmlData += "\n<project name=\""+ brain->name() + "\">";
    increaseIndents();
    
    xmlData += writeIndents() + "<nodetypes>";
    increaseIndents();
    for(int i = 2; i < brain->nodeTypes.count(); i++)
    {
        xmlData += brain->nodeTypes[i]->toNodeTypeXml();
    }
    decreaseIndents();
    xmlData += writeIndents() + "</nodetypes>";

    xmlData += writeIndents() +"<behaviortrees>";
    increaseIndents();
    for(int i = 0; i < brain->behaviorTrees.count(); i++)
    {
        xmlData += writeIndents()+ "<behaviortree name=\""+ brain->behaviorTrees[i]->name() +"\" description=\"" + brain->behaviorTrees[i]->description() + "\" uid=\"" + QVariant(i).toString() + "\">";
        
        increaseIndents();        
        xmlData +=  qobject_cast<btEditorNode*>(brain->behaviorTrees[i]->rootNode()->child(0))->toXml(brain->behaviorTrees);
        decreaseIndents();
        
        xmlData += writeIndents()+"</behaviortree>";
    }
    decreaseIndents();
    xmlData += writeIndents() + "</behaviortrees> ";

    decreaseIndents();
    xmlData += "\n</project>";
    
    return xmlData;
}

void projectParser::increaseIndents()
{
    m_indentCount++;
}

void projectParser::decreaseIndents()
{
    m_indentCount--;
}

const QString projectParser::writeIndents()
{
    QString indents = "\n";
    for (int i = 0; i < m_indentCount; i++) 
    {
        indents += "\t";
    }
    
    return indents;
}

#include "projectparser.moc"