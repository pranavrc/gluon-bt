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
    GameItem();
    GameItem(Game* game);
    GameItem(int x,int y,Game* game);
    enum Direction { Up = 0, Down, Left, Right};
    virtual void setSquare(int x,int y);
public Q_SLOTS:
    bool goUp();
    bool goDown();
    bool goLeft();
    bool goRight();
Q_SIGNALS:
    void actionFailed();
public:
    bool blocks();
    void setBlocks(bool value);
    void setupAnimation();
    void setAnimationStep(QPoint from, QPoint to,Direction dir);
    QTimeLine *timer;
    void setDirection(Direction direction);
    Direction direction() const;
    bool move(Direction dir);
    GameItem* occupant;
    QPoint square;
protected:
    QPolygonF myPolygon;
    bool blocking;
    QGraphicsItemAnimation *animation;
    Direction dir;
    int delay;
public Q_SLOTS:
    void animationDone();
protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant &value);
    Game* game;
};

#endif // GAMEITEM_H
