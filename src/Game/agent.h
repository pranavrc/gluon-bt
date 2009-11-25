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
    QWaitCondition *waitCond;
    void setMutex(QMutex *mutex){this->mutex = mutex;}
    void setWaitCondition(QWaitCondition *waitCond){this->waitCond = waitCond;}
    bool returnValue;
public Q_SLOTS:
    void sayHello();
    void unlock();

    bool relativeLeft();
    bool relativeRight();
    bool forward();
    bool back();
    bool stopMove();
};

#endif // AGENT_H
