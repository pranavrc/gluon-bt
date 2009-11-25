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
    qDebug() << "moveAway::run()";
    Enemy* e = (Enemy*)self;

    if(e->target->game->marker->square.x() < e->target->square.x()){
        return ((Enemy*)self)->goRight();
    }else{
        return ((Enemy*)self)->goLeft();
    }
}

