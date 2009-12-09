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
public Q_SLOTS:
    virtual void sayHello();
    virtual void unlock();

    bool relativeLeft();
    bool relativeRight();
    bool forward();
    bool back();
    bool stopMove();
    bool collision();
};

#endif // AGENT_H
