#include "btwonnode.h"

#include <QDebug>
#include <QThread>
#include "enemy.h"
#include "agent.h"
#include <QBrush>
#include <QColor>


REGISTER_NODETYPE(btWonNode)

btWonNode::btWonNode()
{
    // init variables
}

bool btWonNode::run(btCharacter *self)
{ 
    while(!stopFlag() && self->continueThinking()){
        // dette her er noget en parallel skal h�ndtere
        // qDebug() << "condition called";
        ((Enemy*)self)->eventMutex.lock();
        ((Enemy*)self)->eventCond.wait(&((Enemy*)self)->eventMutex, 30000);
        if(((Enemy*)self)->target->square.x() == property("x").toInt()){
            if(((Enemy*)self)->target->square.y() == property("y").toInt()){
                ((Enemy*)self)->eventMutex.unlock();
                return true;
            }

        }
        ((Enemy*)self)->eventMutex.unlock();
    }
    return false;
}

#include "btwonnode.moc"
