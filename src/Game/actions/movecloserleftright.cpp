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
    qDebug() << "moveCloser::run()";
    Enemy* e = (Enemy*)self;
    qDebug() << "enemy.x " << e->target->game->marker->square.x() << "self.x " <<  e->target->square.x();
    if(e->target->game->marker->square.x() >= e->target->square.x()){
        return ((Enemy*)self)->goRight();
    }else{
        return ((Enemy*)self)->goLeft();
    }
}

