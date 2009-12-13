#include "btgoalnode.h"

#include <QDebug>
#include <QThread>
#include "enemy.h"
#include "agent.h"
#include "game.h"
#include <QBrush>
#include <QColor>


REGISTER_NODETYPE(btGoalNode)

btGoalNode::btGoalNode()
{
    // init variables
}

bool btGoalNode::run(btCharacter *self)
{ 
    while(true){
        // dette her er noget en parallel skal håndtere
            qDebug() << "condition called";
            ((Enemy*)self)->eventMutex.lock();
        ((Enemy*)self)->eventCond.wait(&((Enemy*)self)->eventMutex);
          if(((Enemy*)self)->target->game->board[((Enemy*)self)->target->square.x()][((Enemy*)self)->target->square.y()]->goal()){
              ((Enemy*)self)->target->game->board[((Enemy*)self)->target->square.x()][((Enemy*)self)->target->square.y()]->setGoal(false);
            ((Enemy*)self)->eventMutex.unlock();
            qDebug("found a goal HAHAH");
            return true;
        }
             ((Enemy*)self)->eventMutex.unlock();
    }
    return false;
}

#include "btgoalnode.moc"
