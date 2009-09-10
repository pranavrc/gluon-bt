#include "btreferencenode.h"

btReferenceNode::btReferenceNode()
{
    setNodeType(btNodeType::ReferenceNodeType);
}

btReferenceNode::~btReferenceNode()
{
}

bool btReferenceNode::run()
{
	return false;
}

#include "btreferencenode.moc"