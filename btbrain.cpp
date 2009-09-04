#include "btbrain.h"
#include "bttreemodel.h"
#include "btnodetypesmodel.h"
#include "btnodetype.h"
#include "btnode.h"

btBrain::btBrain(QObject *parent)
{
    btNodeType *node = new btNodeType();
    node->setName("Sequence");
    node->setDescription("A sequence of behaviors, launched in order (fails if one fails)");
    node->setCategory(btNodeType::CompositeCategory);
    nodeTypes.append(node);

    node = new btNodeType();
    node->setName("Selector");
    node->setDescription("A collection of behaviors which are launched in order, until one succeeds (only fails if all fails)");
    node->setCategory(btNodeType::CompositeCategory);
    nodeTypes.append(node);

    node = new btNodeType();
    node->setName("Parallel");
    node->setDescription("A collection of behaviors which are launched at the same time");
    node->setCategory(btNodeType::CompositeCategory);
    nodeTypes.append(node);

    node = new btNodeType();
    node->setName("Random");
    node->setDescription("A collection of behaviors from which is selected one to be launched");
    node->setCategory(btNodeType::CompositeCategory);
    nodeTypes.append(node);

    node = new btNodeType();
    node->setName("InBehavior");
    node->setDescription("Check whether you are in a specified behavior");
    node->setCategory(btNodeType::ConditionCategory);
    nodeTypes.append(node);
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
    btTreeModel *newTree = new btTreeModel(this);
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
    newType->setCategory(btNodeType::ReferenceCategory);
    
    // Finally inform those around us of this wonderful occurrence 
    emit behaviorTreeAdded(newTree);
    emit nodeTypeAdded(newType);
    
    return newTree;
}

void btBrain::deleteBehaviorTree(btTreeModel *behaviorTree)
{
    behaviorTrees.removeAll(behaviorTree);
}

#include "btbrain.moc"
