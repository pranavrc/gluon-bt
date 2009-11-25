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
    qDebug() << "moveAway::run()";
    Enemy* e = (Enemy*)self;

    if(e->target->game->marker->square.y() > e->target->square.y()){
        return ((Enemy*)self)->goUp();
    }else{
        return ((Enemy*)self)->goDown();
    }
}

