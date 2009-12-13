#include "btsequencenode.h"

#include "btnode.h"
#include "btcharacter.h"

btSequenceNode::btSequenceNode()
{
}

bool btSequenceNode::run(btCharacter *self)
{
    for(int i = 0; i < parentNode()->childCount(); i++)
    {
        /*if(stopFlag()){
            return false;
        }*/
        if(!parentNode()->child(i)->runBehavior(self))
        {
            return false;
        }
    }
    
    return true;
}

#include "btsequencenode.moc"
