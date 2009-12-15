#include "movecloserleftrightpinky.h"

#include <QDebug>
#include <QtCore/QThread>
#include <QtCore>
#include "enemy.h"
#include "agent.h"
#include "game.h"

REGISTER_NODETYPE(moveCloserLeftRightPinky)



moveCloserLeftRightPinky::moveCloserLeftRightPinky()
{
    // init variables
}

bool moveCloserLeftRightPinky::run(btCharacter *self)
{
    //qDebug() << "moveCloser::run()";
    Enemy* e = (Enemy*)self;
    //qDebug() << "enemy.x " << e->target->game->marker->square.x() << "self.x " <<  e->target->square.x();
    
    int currentX = 15;
    int currentDelta = 15;
    QPoint targetSquare = pinkySquare(e->target->square,e->target->direction());

    foreach(Agent* a, e->target->getObjectives())
    {
        int delta;
        if(a->square.x() < e->target->square.x())
        {
            delta = targetSquare.x() - a->square.x();
        }
        else
        {
            delta = a->square.x() - targetSquare.x();
        }
        
        if(currentDelta > delta)
        {
            currentDelta = delta;
            currentX = a->square.x();
        }
    }
    //((Enemy*)self)->target->direction()
    
    if(currentX >= targetSquare.x()){
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

#include "movecloserleftrightpinky.moc"
