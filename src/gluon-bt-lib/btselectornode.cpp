#include "btselectornode.h"

#include "btnode.h"
#include "btcharacter.h"

btSelectorNode::btSelectorNode()
{
}

bool btSelectorNode::run(btCharacter *self)
{
    for(int i = 0; i < parentNode()->childCount(); i++)
    {
        if(stopFlag()){
            return false;
        }
        if(parentNode()->child(i)->runBehavior(self))
        {
            return true;
        }
    }
    
    return false;
}

#include "btselectornode.moc"
