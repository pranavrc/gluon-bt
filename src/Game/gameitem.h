#ifndef GAMEITEM_H
#define GAMEITEM_H

#include <QGraphicsPolygonItem>

class Game;
#include <QTimeLine>
#include <QGraphicsItemAnimation>

class GameItem : public QObject, public QGraphicsPolygonItem
{
    Q_OBJECT
    Q_ENUMS(Direction)
public:
    GameItem(Game* game);
    GameItem(int x,int y,Game* game);
    enum Direction { Up = 0, Down, Left, Right};
    void setSquare(int x,int y);
    bool goUp();
    bool goDown();
    bool goLeft();
    bool goRight();
    bool blocks();
    void setBlocks(bool value);
    void setupAnimation();
    void setAnimationStep(QPoint from, QPoint to,Direction dir);
    QTimeLine *timer;
    void setDirection(Direction direction);
     Direction direction() const;
    bool move(Direction dir);
private:
    QPolygonF myPolygon;
    QPoint square;
    Game* game;
    bool blocking;
    QGraphicsItemAnimation *animation;
    Direction dir;
public Q_SLOTS:
    void animationDone();
protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant &value);
};

#endif // GAMEITEM_H
