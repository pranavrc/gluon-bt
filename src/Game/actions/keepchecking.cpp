#include "keepchecking.h"

#include <QDebug>
#include <QtCore/QThread>
#include <QtCore>
#include "enemy.h"
#include "agent.h"
#include "player.h"
#include "game.h"

REGISTER_NODETYPE(keepChecking)

keepChecking::keepChecking()
{
    // init variables
}

bool keepChecking::run(btCharacter *self)
{
    while(!stopFlag() && self->continueThinking()){
        ((Enemy*)self)->eventMutex.lock();
                ((Enemy*)self)->eventCond.wait(&((Enemy*)self)->eventMutex, 30000);
                qDebug() << "is close enough";
                if(parentNode()->child(0)->runBehavior(self) == true){
                    ((Enemy*)self)->eventMutex.unlock();
                    qDebug() << "yes it is";
                    setStopFlag(false);
                    return true;
                }
        
        ((Enemy*)self)->eventMutex.unlock();

    }
    setStopFlag(false);
    return false;
}

#include "keepchecking.moc"
