#include "enemy.h"
#include "agent.h"

Enemy::Enemy()
{
}

Enemy::Enemy(Agent *target,btNode* tree)
{
    this->target = target;
    this->target->setMutex(&(this->mutex));
    this->target->setWaitCondition(&(this->finished));
    this->tree = tree;
    QObject::connect(this, SIGNAL(goDownSignal()),
                     this->target, SLOT(goDown()));
    QObject::connect(this, SIGNAL(goUpSignal()),
                     this->target, SLOT(goUp()));
    QObject::connect(this, SIGNAL(goLeftSignal()),
                     this->target, SLOT(goLeft()));
    QObject::connect(this, SIGNAL(goRightSignal()),
                     this->target, SLOT(goRight()));
}

bool Enemy::goDown()
{
    emit goDownSignal();
}

bool Enemy::goUp()
{
    emit goUpSignal();
}

bool Enemy::goLeft()
{
    emit goLeftSignal();
}

bool Enemy::goRight()
{
    emit goRightSignal();
}

bool Enemy::start()
{
    this->tree->runBehavior(this);
}
