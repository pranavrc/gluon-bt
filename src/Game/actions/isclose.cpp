#include "isclose.h"

#include <QDebug>
#include <QtCore/QThread>
#include <QtCore>
#include "enemy.h"
#include "agent.h"
#include "player.h"
#include "game.h"

REGISTER_NODETYPE(isClose)

isClose::isClose()
{
    // init variables
}

bool isClose::run(btCharacter *self)
{
    Enemy* e = (Enemy*)self;

    int currentX = 15;
    int currentDelta = 15;
    int delta = 0;

    int distance = property("distance").toInt();


    foreach(Agent* a, e->target->getObjectives())
    {

        delta = (a->square - e->target->square).manhattanLength();

        /*if(a->square.x() < e->target->square.x())
        {
            delta = e->target->square.x() - a->square.x();
        }
        else
        {
            delta = a->square.x() - e->target->square.x();
        }*/

        if(currentDelta > delta)
        {
            currentDelta = delta;
            //currentX = a->square.x();
        }
    }
    qDebug() << e->thename << " currentDelta: " << currentDelta;


    if(currentDelta < distance){
        return true;
    }else{
        return false;
    }
}

#include "isclose.moc"
