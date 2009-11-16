#ifndef GAME_H
#define GAME_H

#include <QGraphicsScene>
#include "gameitem.h"

class Game : public QGraphicsScene
{
public:
    Game();
    GameItem *marker;
    void drawItems();
    GameItem* board[16][16];
private:

};

#endif // GAME_H
