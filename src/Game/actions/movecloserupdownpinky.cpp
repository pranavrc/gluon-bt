#include "movecloserupdownpinky.h"
#include "movecloserleftrightpinky.h"

#include <QDebug>
#include <QtCore/QThread>
#include <QtCore>
#include "enemy.h"
#include "agent.h"
#include "game.h"

REGISTER_NODETYPE(moveCloserUpDownPinky)

moveCloserUpDownPinky::moveCloserUpDownPinky()
{
    // init variables
}

bool moveCloserUpDownPinky::run(btCharacter *self)
{
    //qDebug() << "moveCloser::run()";
    Enemy* e = (Enemy*)self;
    //qDebug() << "enemy.y " << e->target->game->marker->square.y() << "self.y " <<  e->target->square.y();
    
    QPoint targetSquare = pinkySquare(e->target->square,e->target->direction());

    int currentY = 15;
    int currentDelta = 15;
    foreach(Agent* a, e->target->getObjectives())
    {
        int delta;
        if(a->square.y() < e->target->square.y())
        {
            delta = targetSquare.y() - a->square.y();
        }
        else
        {
            delta = a->square.y() - targetSquare.y();
        }
        
        if(currentDelta > delta)
        {
            currentDelta = delta;
            currentY = a->square.y();
        }
    }
    
    if(currentY <= targetSquare.y()){
        return ((Enemy*)self)->goUp();
    }else{
        return ((Enemy*)self)->goDown();
    }
    
    /*if(e->target->objective()->square.y() <= e->target->square.y()){
        return ((Enemy*)self)->goUp();
    }else{
        return ((Enemy*)self)->goDown();
    }*/
}


#include "movecloserupdownpinky.moc"
