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

    void stopMoveSignal();
    void forwardSignal();
    void backSignal();
    void relativeLeftSignal();
    void relativeRightSignal();

public:
    bool start();
    bool goUp();
    bool goDown();
    bool goLeft();
    bool goRight();

    bool forward();
    bool back();
    bool relativeLeft();
    bool relativeRight();

    bool stopMove();
    QWaitCondition finished;
    QMutex mutex;
    QWaitCondition eventCond;
    QMutex eventMutex;
    Agent* target;
private:
    btNode* tree;
    btNode* current;
};

#endif // ENEMY_H
