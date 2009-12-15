#include "guard.h"
#include "agent.h"
#include "game.h"



Guard::Guard(Game* game,QPoint pos)
        : Agent(game,pos)
{
    this->setZValue(12);
}

void Guard::sayHello()
{
    Agent::sayHello();
    //QColor color = game->board[square.x()][square.y()]->brush().color().darker(110);
    //game->board[square.x()][square.y()]->setBrush(QBrush(color));
}
