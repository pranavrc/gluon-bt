#include "moveawayupdown.h"

#include <QDebug>
#include <QtCore/QThread>
#include <QtCore>
#include "enemy.h"
#include "agent.h"
#include "game.h"

REGISTER_NODETYPE(moveAwayUpDown)

moveAwayUpDown::moveAwayUpDown()
{
    // init variables
}

bool moveAwayUpDown::run(btCharacter *self)
{
   // qDebug() << "moveAway::run()";
    Enemy* e = (Enemy*)self;
    Agent* closest = e->target->getObjectives().first();

    int currentY = 15;
    int currentDelta;
    foreach(Agent* a, e->target->getObjectives())
    {
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
            a->setPen(QPen(Qt::SolidLine));
            closest = a;
        }
    }

    closest->setPen(QPen(Qt::DotLine));
    
    if(currentY > e->target->square.y()){
        return ((Enemy*)self)->goUp();
    }else{
        return ((Enemy*)self)->goDown();
    }

    /*if(e->target->objective()->square.y() > e->target->square.y()){
        return ((Enemy*)self)->goUp();
    }else{
        return ((Enemy*)self)->goDown();
    }*/
}

#include "moveawayupdown.moc"
