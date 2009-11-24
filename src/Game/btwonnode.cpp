#include "btwonnode.h"

#include <QDebug>
#include <QThread>
#include "enemy.h"
#include "agent.h"

REGISTER_NODETYPE(btWonNode)

btWonNode::btWonNode()
{
    // init variables
}

bool btWonNode::run(btCharacter *self)
{ 
    //((Enemy*)self)->mutex.lock();
    while(true){
            qDebug() << "condition called";
      //  ((Enemy*)self)->mutex.lock();
        ((Enemy*)self)->finished.wait(&((Enemy*)self)->mutex,2000);
          if(((Enemy*)self)->target->square.x() == property("x").toInt()){
        if(((Enemy*)self)->target->square.y() == property("y").toInt()){

            return true;
        }
    }

    }
    /*if(((Enemy*)self)->target->square.x() == property("x").toInt()){
        if(((Enemy*)self)->target->square.y() == property("y").toInt()){
            return true;
        }
    }*/
    //qDebug() << "lol";
    return false;
}

