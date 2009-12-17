#ifndef AGENT_H
#define AGENT_H

#include <QObject>
//#include "game.h"
#include "gameitem.h"
#include "btlib.h"
#include <QThread>
#include <QtCore>

class Game;

class Agent : public GameItem
{
    Q_OBJECT
public:
    Agent();
    Agent(Game* game);
    Agent(Game* game,QPoint pos);
    void setSquare(int x,int y);
    QMutex *mutex;
    QMutex *eventMutex;
    QWaitCondition *waitCond;
    QWaitCondition *eventCond;
    void setMutex(QMutex *mutex){this->mutex = mutex;}
    void setWaitCondition(QWaitCondition *waitCond){this->waitCond = waitCond;}

    void setEventMutex(QMutex *eventMutex){this->eventMutex = eventMutex;}
    void setEventCondition(QWaitCondition *eventCond){this->eventCond = eventCond;}

    bool returnValue;
    bool collided;

    void paint(QPainter *painter,
                           const QStyleOptionGraphicsItem *option,
                           QWidget *widget);
    bool collision();
    
    QList<Agent*> getObjectives();
    void addObjective(Agent* o);

    QList<GameItem*> getGoals();
    void addGoal(GameItem* o);

public Q_SLOTS:
    virtual void sayHello();
    virtual void unlock();

    bool relativeLeft();
    bool relativeRight();
    bool forward();
    bool back();
    bool stopMove();

Q_SIGNALS:
    void enteredNewCell(int x,int y);
    
private:
    QList<Agent*> objectives;
    QList<GameItem*> goals;
};

#endif // AGENT_H
