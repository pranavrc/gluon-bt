#include "btselectornode.h"

#include "btnode.h"

btSelectorNode::btSelectorNode()
{
}

bool btSelectorNode::run()
{
    for(int i = 0; i < parentNode()->childCount(); i++)
    {
        if(parentNode()->child(i)->runBehavior())
        {
            return true;
        }
    }
    
    return false;
}

#include "btselectornode.moc"