#include "btbrain.h"
#include "bttreemodel.h"
#include "btnodetypesmodel.h"
#include "btnodetype.h"
#include "btnode.h"
#include "btcompositenode.h"
#include "btconditionnode.h"
#include <QtCore/qtextstream.h>

btBrain::btBrain(QObject *parent)
{
    btCompositeNode *compositeNode = new btCompositeNode();
    compositeNode->setName("Sequence");
    compositeNode->setDescription("A sequence of behaviors, launched in order (fails if one fails)");
    nodeTypes.append(compositeNode);

    compositeNode = new btCompositeNode();
    compositeNode->setName("Selector");
    compositeNode->setDescription("A collection of behaviors which are launched in order, until one succeeds (only fails if all fails)");
    nodeTypes.append(compositeNode);

    compositeNode = new btCompositeNode();
    compositeNode->setName("Parallel");
    compositeNode->setDescription("A collection of behaviors which are launched at the same time");
    nodeTypes.append(compositeNode);

    compositeNode = new btCompositeNode();
    compositeNode->setName("Random");
    compositeNode->setDescription("A collection of behaviors from which is selected one to be launched");
    nodeTypes.append(compositeNode);

    btConditionNode * conditionNode = new btConditionNode();
    conditionNode->setName("InBehavior");
    conditionNode->setDescription("Check whether you are in a specified behavior");
    nodeTypes.append(conditionNode);
    
    btDecoratorNode * decoratorNode = new btDecoratorNode();
    decoratorNode->setName("Resource Guard");
    decoratorNode->setDescription("Make sure that a specific resource is available before accepting traversal into the associated node");
    nodeTypes.append(decoratorNode);
}

btBrain::~btBrain()
{
    qDeleteAll(nodeTypes);
    qDeleteAll(behaviorTrees);
}

btNodeType *btBrain::findNodeTypeByName(QString name)
{
    foreach(btNodeType *nodeType, nodeTypes)
        if(nodeType->name() == name)
            return nodeType;
    return 0;
}

btTreeModel *btBrain::newBehaviorTree()
{
    // First create the new BT
    btTreeModel *newTree = new btTreeModel(this, this);
    this->behaviorTrees.append(newTree);
    newTree->setName(tr("New Tree"));
    // We set the root node to be a sequence, as this is the fastest to choose that it should simply run the first child node (no selection, just runs children in sequence)
    btNode *btRootNode = new btNode(this->findNodeTypeByName("Sequence"));
    newTree->setRootNode(btRootNode);
    
    // Add a real top level node, which should be a selector as per Alex' defintion of behavior trees
    btNode *topNode = new btNode(this->findNodeTypeByName("Selector"));
    topNode->setName(tr("Top Beavior"));
    btRootNode->appendChild(topNode);
    
    // Then add it to the list of referenced NodeTypes...
    btNodeType *newType = new btNodeType(this);
    newType->setName(newTree->name());
    newType->setDescription(tr("A reference to the behavior tree named %1").arg(newTree->name()));
    newType->setNodeType(btNodeType::ReferenceNodeType);
    
    // Finally inform those around us of this wonderful occurrence 
    emit behaviorTreeAdded(newTree);
    emit nodeTypeAdded(newType);
    
    return newTree;
}

void btBrain::deleteBehaviorTree(btTreeModel *behaviorTree)
{
    behaviorTrees.removeAll(behaviorTree);
}

void btBrain::setName(QString name) { m_name = name; }
QString btBrain::name() const { return m_name; }

void btBrain::addBehaviorTree(btTreeModel* newTree)
{
    behaviorTrees.append(newTree);
    emit behaviorTreeAdded(newTree);
}

void btBrain::addNodeType(btNodeType* newNodeType)
{
    nodeTypes.append(newNodeType);
    emit nodeTypeAdded(newNodeType);
}
#include "btbrain.moc"
