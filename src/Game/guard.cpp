#include "guard.h"
#include "agent.h"
#include "game.h"



Guard::Guard(Game* game,QPoint pos)
        : Agent(game,pos)
{
    this->setZValue(9);
}
