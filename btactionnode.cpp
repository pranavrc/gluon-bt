#include "btactionnode.h"

btActionNode::btActionNode(QObject* parent)
{
    setNodeType(btNodeType::ActionNodeType);
}

btActionNode::~btActionNode()
{
}

#include "btactionnode.moc"