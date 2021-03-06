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
//    Player* occupant = static_cast<Player*>(((Enemy*)self)->target->game->board[((Enemy*)self)->target->square.x()][((Enemy*)self)->target->square.y()]->occupant);

    while(!stopFlag() && self->continueThinking()){
        ((Enemy*)self)->eventMutex.lock();
                ((Enemy*)self)->eventCond.wait(&((Enemy*)self)->eventMutex, 30000);

                if(((Enemy*)self)->collision() == true){
                    //qDebug() << "behavior tree collision detected";
                    ((Enemy*)self)->eventMutex.unlock();
                    setStopFlag(false);
                    return true;
                }
        
        ((Enemy*)self)->eventMutex.unlock();

    }
    setStopFlag(false);
    return false;
}

#include "iscollided.moc"
