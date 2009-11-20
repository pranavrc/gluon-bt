#include "enemy.h"
#include "agent.h"

#include <QDateTime>

Enemy::Enemy()
{
}

Enemy::Enemy(Agent *target,btNode* tree)
{
    qsrand(QDateTime::currentDateTime().toTime_t());
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
    this->mutex.lock();
    this->finished.wait(&(this->mutex));
    return this->target->returnValue;
}

bool Enemy::goUp()
{
    emit goUpSignal();
    this->mutex.lock();
    this->finished.wait(&(this->mutex));
    return this->target->returnValue;
}

bool Enemy::goLeft()
{
    emit goLeftSignal();
    this->mutex.lock();
    this->finished.wait(&(this->mutex));
    return this->target->returnValue;
}

bool Enemy::goRight()
{
    emit goRightSignal();
    this->mutex.lock();
    this->finished.wait(&(this->mutex));
    return this->target->returnValue;
}

bool Enemy::start()
{
    this->tree->runBehavior(this);
}
