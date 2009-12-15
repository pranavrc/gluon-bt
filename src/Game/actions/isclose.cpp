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
    int currentDelta = 30;
    int delta = 0;

    int distance = property("distance").toInt();
    Agent* closest = e->target->getObjectives().first();
    closest->setPen(QPen(Qt::SolidLine));

    foreach(Agent* a, e->target->getObjectives())
    {
        delta = (a->square - e->target->square).manhattanLength();
        qDebug() << "squares: " << a->square << e->target->square << "man: " << delta;

        /*if(a->square.x() < e->target->square.x())
        {
            delta = e->target->square.x() - a->square.x();
        }
        else
        {
            delta = a->square.x() - e->target->square.x();
        }*/

        a->setPen(QPen(Qt::SolidLine));

        if(currentDelta > delta)
        {
            currentDelta = delta;
            closest = a;
            qDebug() << e->thename << " currentDelta: " << currentDelta;
                qDebug() << e->thename << " closest: " << a->square;
            //currentX = a->square.x();
                //qDebug() << e->target->metaObject()->className();
        }
    }
    closest->setPen(QPen(Qt::DotLine));



    if(currentDelta < distance){
        if(e->target->metaObject()->className() == "Player")
            e->target->setBrush(QColor(Qt::blue));
        return true;
    }else{
        if(e->target->metaObject()->className() == "Player")
            e->target->setBrush(QColor(Qt::magenta));
        return false;
    }
}

#include "isclose.moc"
