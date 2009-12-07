#include "iscollided.h"

#include <QDebug>
#include <QtCore/QThread>
#include <QtCore>
#include "enemy.h"
#include "agent.h"
#include "player.h"
#include "game.h"

REGISTER_NODETYPE(isCollided)

isCollided::isCollided()
{
    // init variables
}

bool isCollided::run(btCharacter *self)
{
    Player* occupant = static_cast<Player*>(((Enemy*)self)->target->game->board[((Enemy*)self)->target->square.x()][((Enemy*)self)->target->square.y()]->occupant);

    while(true){
        ((Enemy*)self)->eventMutex.lock();
                ((Enemy*)self)->eventCond.wait(&((Enemy*)self)->eventMutex);
        if((occupant != NULL) && (occupant != ((Enemy*)self)->target)){
            if(occupant->square == ((Enemy*)self)->target->square){
               occupant->collided();
                ((Enemy*)self)->eventMutex.unlock();
                return true;
            }

        }
        ((Enemy*)self)->eventMutex.unlock();

    }
    return false;
}

