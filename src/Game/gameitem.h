#ifndef GAMEITEM_H
#define GAMEITEM_H

#include <QGraphicsPolygonItem>
//#include "game.h"

class Game;

class GameItem : public QGraphicsPolygonItem
{
public:
    GameItem(Game* game);
    GameItem(int x,int y,Game* game);
    void setSquare(int x,int y);
    bool goUp();
    bool goDown();
    bool goLeft();
    bool goRight();
    bool blocks();
    void setBlocks(bool value);
private:
    QPolygonF myPolygon;
    QPoint square;
    Game* game;
    bool blocking;
protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant &value);
};

#endif // GAMEITEM_H
