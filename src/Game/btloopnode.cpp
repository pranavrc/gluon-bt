#include "btloopnode.h"

REGISTER_NODETYPE(btLoopNode)

        btLoopNode::btLoopNode()
{
}

bool btLoopNode::run(btCharacter *self)
{
    while(true){
        for(int i = 0; i < parentNode()->childCount(); i++)
        {
            if(!parentNode()->child(i)->runBehavior(self))
            {
                return false;
            }
        }
    }
    
    return true;
}
