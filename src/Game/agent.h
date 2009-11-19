#ifndef AGENT_H
#define AGENT_H

#include <QObject>
#include "game.h"
#include "gameitem.h"
#include "btlib.h"
#include <QThread>
#include <QtCore>

class Agent : public GameItem
{
    Q_OBJECT
public:
    Agent();
    Agent(Game* game);
    Agent(Game* game,QPoint pos);
    GameItem::Direction choose();
    void setSquare(int x,int y);
    QMutex *mutex;
    QWaitCondition *waitCond;
    void setMutex(QMutex *mutex){this->mutex = mutex;}
    void setWaitCondition(QWaitCondition *waitCond){this->waitCond = waitCond;}
public Q_SLOTS:
    void sayHello();
    void unlock();
};

#endif // AGENT_H
