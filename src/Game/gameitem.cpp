#include "gameitem.h"
#include <QDebug>
#include "game.h"

GameItem::GameItem(Game* game)
{
    myPolygon << QPointF(-10, 0) << QPointF(0, 10)
                      << QPointF(10, 0) << QPointF(0, -10)
                      << QPointF(-10, 0);
    this->setPolygon(myPolygon);
      setFlag(QGraphicsItem::ItemIsMovable, true);
   setFlag(QGraphicsItem::ItemIsSelectable, true);
    setSquare(0,0);
    this->game = game;
}

GameItem::GameItem(int x,int y,Game* game){
    myPolygon << QPointF(-10, 0) << QPointF(0, 10)
                      << QPointF(10, 0) << QPointF(0, -10)
                      << QPointF(-10, 0);
    this->setPolygon(myPolygon);

    setSquare(x,y);
    this->game = game;

}

void GameItem::setSquare(int x,int y){
    square.setX(x);
    square.setY(y);
    setPos((x * 20)+ 10,(y * 20) +10);
}

QVariant GameItem::itemChange(GraphicsItemChange change,
                     const QVariant &value)
{
    qDebug() << "item changed";

    return value;
}

bool GameItem::goUp()
{
    qDebug("going up");
    if(square.y() > 0 && !(game->board[square.x()][square.y() - 1]->blocks())){
        game->board[square.x()][square.y()]->setVisible(false);
        setSquare(square.x(),square.y() - 1);
        return true;
    }
    return false;
}

bool GameItem::goDown()
{
    qDebug("going down");
    if(square.y() < 16 && !(game->board[square.x()][square.y() + 1]->blocks())){
        qDebug("going down 2");
        game->board[square.x()][square.y()]->setVisible(false);
        setSquare(square.x(),square.y() + 1);
        return true;
    }
    return false;
}

bool GameItem::goLeft()
{
    qDebug("going left");
    if(square.x() > 0 && !game->board[square.x() - 1][square.y()]->blocks()){
        game->board[square.x()][square.y()]->setVisible(false);
        setSquare(square.x() - 1,square.y());
        return true;
    }
    return false;
}

bool GameItem::goRight()
{
    qDebug("going right");
    if(square.x() < 16 && !game->board[square.x() + 1][square.y()]->blocks()){
        game->board[square.x()][square.y()]->setVisible(false);
        setSquare(square.x() + 1,square.y());
        return true;
    }
    return false;
}

bool GameItem::blocks()
{
    return blocking;
}

void GameItem::setBlocks(bool value)
{
    blocking = value;
}
