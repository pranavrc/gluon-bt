#include "btdecoratornode.h"

btDecoratorNode::btDecoratorNode()
{
    setNodeType(btNodeType::DecoratorNodeType);
}

btDecoratorNode::~btDecoratorNode()
{
}

bool btDecoratorNode::run()
{
	return false;
}

#include "btdecoratornode.moc"