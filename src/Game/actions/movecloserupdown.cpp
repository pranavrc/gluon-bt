#include "movecloserupdown.h"

#include <QDebug>
#include <QtCore/QThread>
#include <QtCore>
#include "enemy.h"
#include "agent.h"
#include "game.h"

REGISTER_NODETYPE(moveCloserUpDown)

moveCloserUpDown::moveCloserUpDown()
{
    // init variables
}

bool moveCloserUpDown::run(btCharacter *self)
{
    qDebug() << "moveCloser::run()";
    Enemy* e = (Enemy*)self;
    qDebug() << "enemy.y " << e->target->game->marker->square.y() << "self.y " <<  e->target->square.y();
    if(e->target->game->marker->square.y() <= e->target->square.y()){
        return ((Enemy*)self)->goUp();
    }else{
        return ((Enemy*)self)->goDown();
    }
}

