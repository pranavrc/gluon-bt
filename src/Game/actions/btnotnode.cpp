#include "btnotnode.h"

REGISTER_NODETYPE(btNotNode)

        btNotNode::btNotNode()
{
}

bool btNotNode::run(btCharacter *self)
{

	return !(parentNode()->child(0)->runBehavior(self));

}

#include "btnotnode.moc"
