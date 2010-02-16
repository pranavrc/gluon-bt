#include "btreferencenode.h"

btReferenceNode::btReferenceNode()
{
}
btReferenceNode::~btReferenceNode()
{
}

btNode::status btReferenceNode::run(btCharacter * self)
{
	if(this->currentChildStatus() == btNode::None)
		return this->currentChildStatus();
	
	return this->runChild(0);
}

void btReferenceNode::addParentNode(btNode* parent)
{
}

btNode* btReferenceNode::getParentNode()
{
}

#include "btreferencenode.moc"