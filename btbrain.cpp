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
    node->setCategory(btNodeType::Composite);
    nodeTypes.append(node);

    node = new btNodeType();
    node->setName("Selector");
    node->setDescription("A collection of behaviors which are launched in order, until one succeeds (only fails if all fails)");
    node->setCategory(btNodeType::Composite);
    nodeTypes.append(node);

    node = new btNodeType();
    node->setName("Parallel");
    node->setDescription("A collection of behaviors which are launched at the same time");
    node->setCategory(btNodeType::Composite);
    nodeTypes.append(node);

    node = new btNodeType();
    node->setName("Random");
    node->setDescription("A collection of behaviors from which is selected one to be launched");
    node->setCategory(btNodeType::Composite);
    nodeTypes.append(node);

    node = new btNodeType();
    node->setName("InBehavior");
    node->setDescription("Check whether you are in a specified behavior");
    node->setCategory(btNodeType::Condition);
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
    btNode *btRootNode = new btNode(this->findNodeTypeByName("Selector"));
    newTree->setRootNode(btRootNode);
    
    // Then add it to the list of referenced NodeTypes...
    btNodeType *newType = new btNodeType(this);
    newType->setName(newTree->name());
    newType->setDescription(tr("A reference to the behavior tree named %1").arg(newTree->name()));
    newType->setCategory(btNodeType::Reference);
    
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
