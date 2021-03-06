#ifndef GAMEITEM_H
#define GAMEITEM_H

#include <QGraphicsPolygonItem>

class Game;
#include <QTimeLine>
#include <QGraphicsItemAnimation>
#include <QMutex>

class GameItem : public QObject, public QGraphicsPolygonItem
{
    Q_OBJECT
    Q_ENUMS(Direction)
public:
    GameItem();
    GameItem(Game* game);
    GameItem(int x,int y,Game* game);
    enum Direction { Up = 0, Down, Left, Right, None};
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
    bool goal();
    void setGoal(bool value);
    void setupAnimation();
    void setAnimationStep(QPoint from, QPoint to,Direction dir);
    QTimeLine *timer;
    void setDirection(Direction direction) { dir = direction; }
    Direction direction() const { return dir; }
    bool move(Direction dir);
    GameItem* occupant;
    QPoint square;
    Game* game;
    bool isGoal;
protected:
    QPolygonF myPolygon;
    bool blocking;
    QGraphicsItemAnimation *animation;
    Direction dir;
    int delay;
    QMutex squareLock;
public Q_SLOTS:
    void animationDone();
protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant &value);

};

#endif // GAMEITEM_H
