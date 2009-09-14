#include "projectparser.h"

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

                for(int j = 0; j < brain->nodeTypes.count(); j++)
                {
                    if(brain->nodeTypes[j]->name() == nodeAttributes.namedItem("nodetype").nodeValue())
                    {
                        newBTNode->setType(brain->nodeTypes[j]->copy());
                        break;
                    }
                }

                newBTNode->setName(nodeAttributes.namedItem("name").nodeValue());
                newBTNode->setDescription(nodeAttributes.namedItem("description").nodeValue());

                behaviorTreesList[nodeAttributes.namedItem("uid").nodeValue().toInt()] = newBTNode;
            }

            //then parse every tree, and link them together
            parseBehaviorTrees(behaviorTrees, brain);
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

        for(int j = 0; j < currentNodeType.childNodes().count(); j++)
        {
            QDomNode currentProperty = currentNodeType.childNodes().at(j);
            QDomNamedNodeMap propertyAttributes = currentProperty.attributes();
            newNode->setProperty(propertyAttributes.namedItem("name").nodeName().toUtf8(), propertyAttributes.namedItem("name").nodeValue());
            newNode->setProperty(propertyAttributes.namedItem("description").nodeName().toUtf8(), propertyAttributes.namedItem("description").nodeValue());
            newNode->setProperty(propertyAttributes.namedItem("datatype").nodeName().toUtf8(), propertyAttributes.namedItem("datatype").nodeValue());
        }

        brain->nodeTypes.append(newNode);
    }
}

void projectParser::parseBehaviorTrees(QDomNode xNode, btNode * node ,btBrain * brain)
{    
    for(int i = 0; i < xNode.childNodes().count(); i++)
    {
        QDomNode currentNode = xNode.childNodes().at(i);
        QDomNode nodeAttributes = currentNode.attributes();

        if(currentNode.nodeName() == "property")
        {

        }
        else
        {
            for(int j = 0; j < nodeAttributes.childNodes().count(); j++)
            {
                QDomNode currentAttribute = nodeAttributes.childNodes().at(j);
                if(currentAttribute.nodeName() == "nodetype")
                {
                    for(int k = 0; k < brain->nodeTypes.count(); k++)
                    {
                        if(brain->nodeTypes[k]->name() == nodeAttributes.namedItem("nodetype").nodeValue())
                        {
                            newBTNode->setType(brain->nodeTypes[k]->copy());
                        }
                    }
                }
                else
                {
                    newBTNode->setProperty(currentNode.nodeName().toUtf8(), currentNode.nodeValue());
                }
            }
        }

        if(currentNode.hasChildNodes())
        {
            parseBehaviorTrees(currentNode, newBTNode,brain);
        }
    }
}

#include "projectparser.moc"
