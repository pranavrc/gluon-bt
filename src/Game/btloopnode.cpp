#include "btloopnode.h"

#include "enemy.h"

REGISTER_NODETYPE(btLoopNode)

btLoopNode::btLoopNode()
{
}

bool btLoopNode::run(btCharacter *self)
{
    while(/*!stopFlag()*/self->continueThinking()){
        for(int i = 0; i < parentNode()->childCount(); i++)
        {
            /*if(stopFlag()){
                setStopFlag(false);
                return false;
            }*/
            
            qDebug() <<"loop: " << ((Enemy*)self)->name();
            
            parentNode()->child(i)->runBehavior(self);
#warning fix conditions!!!!
/*            if(!parentNode()->child(i)->runBehavior(self))
            {
                qDebug("out of loop");
                return false;
            }*/
        }
    }
    //setStopFlag(false);
    return false; // tjek hvad det gør
}

#include "btloopnode.moc"
