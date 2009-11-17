#ifndef AGENT_H
#define AGENT_H

#include <QObject>
#include "game.h"
#include "gameitem.h"
#include "btlib.h"

class Agent : public GameItem
{
    Q_OBJECT
public:
    Agent();
    Agent(Game* game);
    Agent(Game* game,QPoint pos);
    GameItem::Direction choose();
    void setSquare(int x,int y);
public Q_SLOTS:
    void sayHello();
};

#endif // AGENT_H
