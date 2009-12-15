#include "btloopnode.h"

#include "enemy.h"

REGISTER_NODETYPE(btLoopNode)

btLoopNode::btLoopNode()
{

}

bool btLoopNode::run(btCharacter *self)
{
    setStopFlag(false);
    int repeats = -1;
    if(property("repeat").isValid()){
        repeats = property("repeat").toInt();
    }
    qDebug() << "repeat: " << repeats;
    while(!stopFlag() && self->continueThinking() && (repeats != 0)){
        for(int i = 0; i < parentNode()->childCount(); i++)
        {            
            qDebug() <<"loop: " << ((Enemy*)self)->name();
            
            parentNode()->child(i)->runBehavior(self);
#warning fix conditions!!!!

        }
        if(repeats > 0){
            repeats--;
        }
    }
    setStopFlag(false);
    return false; // tjek hvad det gør
}

#include "btloopnode.moc"
