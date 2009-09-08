#include "btconditionnode.h"
#include "btnode.h"

btConditionNode::btConditionNode()
{
    setNodeType(btNodeType::ConditionNodeType);
}

btConditionNode::~btConditionNode()
{
}

#include "btconditionnode.moc"