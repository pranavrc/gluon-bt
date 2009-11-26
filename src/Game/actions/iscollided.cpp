#include "iscollided.h"

#include <QDebug>
#include <QtCore/QThread>
#include <QtCore>
#include "enemy.h"
#include "agent.h"

REGISTER_NODETYPE(isCollided)

isCollided::isCollided()
{
    // init variables
}

bool isCollided::run(btCharacter *self)
{
    while(true){
        // dette her er noget en parallel skal håndtere
        qDebug() << "condition called";
        ((Enemy*)self)->finished.wait(&((Enemy*)self)->mutex,200);
        if(((Enemy*)self)->target->square.x() == property("x").toInt()){
            if(((Enemy*)self)->target->square.y() == property("y").toInt()){

                return true;
            }
        }

    }
    return false;
}

