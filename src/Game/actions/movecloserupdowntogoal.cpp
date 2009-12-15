#include "movecloserupdowntogoal.h"

#include <QDebug>
#include <QtCore/QThread>
#include <QtCore>
#include "enemy.h"
#include "agent.h"
#include "game.h"

REGISTER_NODETYPE(moveCloserUpDownToGoal)

moveCloserUpDownToGoal::moveCloserUpDownToGoal()
{
    // init variables
}

bool moveCloserUpDownToGoal::run(btCharacter *self)
{
    //qDebug() << "moveCloser::run()";
    Enemy* e = (Enemy*)self;
    //qDebug() << "enemy.y " << e->target->game->marker->square.y() << "self.y " <<  e->target->square.y();
    
    int currentY = 15;
    int currentDelta = 15;

    bool isGoal = false;

    GameItem *closest = e->target->getGoals().first();

    foreach(GameItem* a, e->target->getGoals())
    {   
        isGoal = a->goal();
        if(isGoal == false) continue;

        int delta;
        if(a->square.y() < e->target->square.y())
        {
            delta = e->target->square.y() - a->square.y();
        }
        else
        {
            delta = a->square.y() - e->target->square.y();
        }
        
        if(currentDelta > delta)
        {
            currentDelta = delta;
            currentY = a->square.y();
            closest = a;
        }
    }
    
    //closest->setGoal(false);

    if(currentY <= e->target->square.y()){
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


#include "movecloserupdowntogoal.moc"
