#include "btreferencenode.h"

btReferenceNode::btReferenceNode()
{
    setNodeType(btNodeType::ReferenceNodeType);
}

btReferenceNode::~btReferenceNode()
{
}

#include "btreferencenode.moc"