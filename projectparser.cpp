#include "projectparser.h"

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

            btNode *  newBTNode = new btNode();

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
            newBTNode->setParentNode(node);
        }
    }
}

QString projectParser::serializeProject(btBrain * brain) const
{
    QString xmlData = "<?xml version=\"1.0\" encoding=\"UTF-8\" ?>";

    xmlData += "<nodetypes>";
    xmlData += serializeNodeTypes(brain->nodeTypes);
    xmlData += "</nodetypes>";

    xmlData += "<behaviortrees>";
    xmlData += serializeBehaviorTree(brain->behaviorTrees);
    xmlData += "</behaviortrees>";

    return xmlData;
}

QString projectParser::serializeNodeTypes(QList<btNodeType *> nodeTypes) const
{
    QString xmlData = "";

    for(int i = 2; i < nodeTypes.count(); i++)
    {
        if(nodeTypes[i]->type() != btNodeType::ReferenceNodeType)
        {
            xmlData += "<nodetype ";
            xmlData += serializeNodeTypeProperties(nodeTypes[i]);
            xmlData += "</nodetype>";
        }
    }

    return xmlData;
}

QString projectParser::serializeBehaviorTree(QList<btTreeModel *> behaviorTrees) const
{
    QString xmlData = "";

    for(int i = 0; i < behaviorTrees.count(); i++)
    {
        xmlData += "<behaviortree name=\""+ behaviorTrees[i]->name() +"\" description=\"" + behaviorTrees[i]->description() + "\" uid=\"" + QVariant(i).toString() + "\" />";
        xmlData += serializeBehaviorTreeNode(behaviorTrees[i]->rootNode()->child(0), behaviorTrees);
        xmlData += "</behaviortree>";
    }

    return xmlData;
}

QString projectParser::serializeNodeTypeProperties(btNodeType * nodeType) const
{
    QString nodeTypeAttributes = "";
    QString properties = "";

    const QMetaObject * mo = nodeType->metaObject();

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
            nodeTypeAttributes += "name=\"" + nodeType->property(moProperty.name()).toString() + "\" ";
        }
        else if(propertyName == "description")
        {
            nodeTypeAttributes += "description=\"" + nodeType->property(moProperty.name()).toString() + "\" ";
        }
        else if(propertyName == "className")
        {
            nodeTypeAttributes += "classname=\"" + nodeType->property(moProperty.name()).toString() + "\" ";
        }
    }

    switch(nodeType->type())
    {
    case btNodeType::ActionNodeType:
        nodeTypeAttributes += "category=\"action\">";
        break;
    case btNodeType::CompositeNodeType:
        nodeTypeAttributes += "category=\"composite\">";
        break;
    case btNodeType::ConditionNodeType:
        nodeTypeAttributes += "category=\"condition\">";
        break;
    case btNodeType::DecoratorNodeType:
        nodeTypeAttributes += "category=\"decorator\">";
        break;
    case btNodeType::UnusableNodeType:
        nodeTypeAttributes += "category=\"unusable\">";
        break;
    }

    for(int i = 0; i < nodeType->dynamicPropertyNames().count(); i++)
    {
        QString propertyName(nodeType->dynamicPropertyNames().at(i));
        properties += "<property name=\"" + propertyName + "\" description=\"\" datatype=\"";
        properties +=  nodeType->property(propertyName.toUtf8()).toString();
        properties += "\" />";
    }

    return nodeTypeAttributes + properties;
}

QString projectParser::serializeBehaviorTreeNode(btNode * node, QList<btTreeModel *> behaviorTrees) const
{
    QString startTag = "<behaviornode ";
    QString endTag = "</behaviornode>";
    QString properties = "";
    QString children = "";
    btNodeType * nodeType = node->type();
    const QMetaObject * mo = nodeType->metaObject();

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
            startTag += "name=\"" + nodeType->property(moProperty.name()).toString() + "\" ";
        }
        else if(propertyName == "description")
        {
            startTag += "description=\"" + nodeType->property(moProperty.name()).toString() + "\" ";
        }
        else if(propertyName == "className")
        {
            if(nodeType->type() == btNodeType::ReferenceNodeType)
            {
                startTag += "nodetype=\"[reference]\" ";
            }
            else
            {
                startTag += "nodetype=\"" + nodeType->property(moProperty.name()).toString() + "\" ";
            }
        }
    }

    startTag += ">";


    if(nodeType->type() == btNodeType::ReferenceNodeType)
    {
        btReferenceNode * btRefNode = qobject_cast<btReferenceNode*>(nodeType);
        properties = "<property name=\"reference\" value=\"";

        for(int i = 0; i < behaviorTrees.count(); i ++)
        {
            if(btRefNode->referenceBehaviorTree() == behaviorTrees.at(i))
            {
                properties += QVariant(i).toString() +"\" />";
            }
        }
    }
    else
    {
        for(int i = 0; i < nodeType->dynamicPropertyNames().count(); i++)
        {
            QString propertyName(nodeType->dynamicPropertyNames().at(i));
            properties += "<property name=\"" + propertyName + "\" value=\"";
            properties +=  nodeType->property(propertyName.toUtf8()).toString();
            properties += "\" />";
        }
    }

    for(int i = 0; i < node->decoratorCount(); i++)
    {
        children += serializeBehaviorTreeDecorator(node->decorators().at(i));
    }

    for(int i = 0; i < node->childCount(); i++)
    {
        children += serializeBehaviorTreeNode(node->child(i), behaviorTrees);
    }

    return startTag + properties + children + endTag;
}


QString projectParser::serializeBehaviorTreeDecorator(btNodeType * decorator) const
{
    QString startTag = "<decorator ";
    QString endTag = "</decorator>";
    QString properties = "";

    const QMetaObject * mo = decorator->metaObject();

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
            startTag += "name=\"" + decorator->property(moProperty.name()).toString() + "\" ";
        }
        else if(propertyName == "description")
        {
            startTag += "description=\"" + decorator->property(moProperty.name()).toString() + "\" ";
        }
        else if(propertyName == "className")
        {
            startTag += "classname=\"" + decorator->property(moProperty.name()).toString() + "\" ";
        }
    }

    for(int i = 0; i < decorator->dynamicPropertyNames().count(); i++)
    {
        QString propertyName(decorator->dynamicPropertyNames().at(i));
        properties += "<property name=\"" + propertyName + "\" value=\"";
        properties +=  decorator->property(propertyName.toUtf8()).toString();
        properties += "\" />";
    }

    return startTag + properties + endTag;
}

#include "projectparser.moc"
