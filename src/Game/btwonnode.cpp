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
    while(true){
        // dette her er noget en parallel skal håndtere
            qDebug() << "condition called";
        ((Enemy*)self)->eventCond.wait(&((Enemy*)self)->eventMutex);
          if(((Enemy*)self)->target->square.x() == property("x").toInt()){
        if(((Enemy*)self)->target->square.y() == property("y").toInt()){
            return true;
        }
    }

    }
    return false;
}

