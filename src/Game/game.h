#ifndef GAME_H
#define GAME_H

#include <QGraphicsScene>
#include "gameitem.h"

class Game : public QGraphicsScene
{
public:
    Game();
    GameItem *marker;
    GameItem* board[16][16];
};

#endif // GAME_H
