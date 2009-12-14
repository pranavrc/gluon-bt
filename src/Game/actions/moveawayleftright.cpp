#include "moveawayleftright.h"

#include <QDebug>
#include <QtCore/QThread>
#include <QtCore>
#include "enemy.h"
#include "agent.h"
#include "game.h"

REGISTER_NODETYPE(moveAwayLeftRight)

moveAwayLeftRight::moveAwayLeftRight()
{
    // init variables
}

bool moveAwayLeftRight::run(btCharacter *self)
{
    //qDebug() << "moveAway::run()";
    Enemy* e = (Enemy*)self;
    
    int currentX = 15;
    int currentDelta = 15;
    foreach(Agent* a, e->target->getObjectives())
    {
        int delta;
        if(a->square.x() < e->target->square.x())
        {
            delta = e->target->square.x() - a->square.x();
        }
        else
        {
            delta = a->square.x() - e->target->square.x();
        }
        
        if(currentDelta > delta)
        {
            currentDelta = delta;
            currentX = a->square.x();
        }
    }
    
    if(currentX < e->target->square.x()){
        return ((Enemy*)self)->goRight();
    }else{
        return ((Enemy*)self)->goLeft();
    }

    /*if(e->target->objective()->square.x() < e->target->square.x()){
        return ((Enemy*)self)->goRight();
    }else{
        return ((Enemy*)self)->goLeft();
    }*/
}

#include "moveawayleftright.moc"
