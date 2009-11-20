#ifndef ENEMY_H
#define ENEMY_H

#include "btcharacter.h"
#include "btlib.h"
#include <QtCore>

class Agent;

class Enemy : public btCharacter
{
    Q_OBJECT
public:
    Enemy();
    Enemy(Agent *target,btNode* tree);
Q_SIGNALS:
    bool goUpSignal();
    void goDownSignal();
    void goLeftSignal();
    void goRightSignal();

public:
    bool start();
    bool goUp();
    bool goDown();
    bool goLeft();
    bool goRight();
    QWaitCondition finished;
    QMutex mutex;
private:
    Agent* target;
    btNode* tree;
    btNode* current;
};

#endif // ENEMY_H
