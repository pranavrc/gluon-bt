#include "movecloserleftright.h"

#include <QDebug>
#include <QtCore/QThread>
#include <QtCore>
#include "enemy.h"
#include "agent.h"
#include "game.h"

REGISTER_NODETYPE(moveCloserLeftRight)

moveCloserLeftRight::moveCloserLeftRight()
{
    // init variables
}

bool moveCloserLeftRight::run(btCharacter *self)
{
    //qDebug() << "moveCloser::run()";
    Enemy* e = (Enemy*)self;
    //qDebug() << "enemy.x " << e->target->game->marker->square.x() << "self.x " <<  e->target->square.x();
    
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
    
    if(currentX >= e->target->square.x()){
        return ((Enemy*)self)->goRight();
    }else{
        return ((Enemy*)self)->goLeft();
    }
    
    /*if(e->target->objective()->square.x() >= e->target->square.x()){
        return ((Enemy*)self)->goRight();
    }else{
        return ((Enemy*)self)->goLeft();
    }*/
}

#include "movecloserleftright.moc"
