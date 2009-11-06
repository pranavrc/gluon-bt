#include "btsequencenode.h"

#include "btnode.h"

btSequenceNode::btSequenceNode()
{
}

bool btSequenceNode::run()
{
    for(int i = 0; i < parentNode()->childCount(); i++)
    {
        if(!parentNode()->child(i)->runBehavior())
        {
            return false;
        }
    }
    
    return true;
}

#include "btsequencenode.moc"
