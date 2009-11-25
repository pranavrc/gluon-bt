#include "enemy.h"
#include "agent.h"

#include <QDateTime>

Enemy::Enemy()
{
}

Enemy::Enemy(Agent *target,btNode* tree)
{
    qDebug("enemy constructor");
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
        QObject::connect(this, SIGNAL(stopMoveSignal()),
                     this->target, SLOT(stopMove()));
    QObject::connect(this, SIGNAL(forwardSignal()),
                     this->target, SLOT(forward()));
    QObject::connect(this, SIGNAL(backSignal()),
                     this->target, SLOT(back()));
    QObject::connect(this, SIGNAL(relativeLeftSignal()),
                     this->target, SLOT(relativeLeft()));
    QObject::connect(this, SIGNAL(relativeRightSignal()),
                     this->target, SLOT(relativeRight()));
}

bool Enemy::goDown()
{
    qDebug("enemyDown");
    emit goDownSignal();
    this->mutex.lock();
    this->finished.wait(&(this->mutex));
    return this->target->returnValue;
}

bool Enemy::goUp()
{
    qDebug("enemyUp");
    emit goUpSignal();
    this->mutex.lock();
    this->finished.wait(&(this->mutex));
    return this->target->returnValue;
}

bool Enemy::goLeft()
{
    qDebug("enemyLeft");
    emit goLeftSignal();
    this->mutex.lock();
    this->finished.wait(&(this->mutex));
    return this->target->returnValue;
}

bool Enemy::goRight()
{
    qDebug("enemyRight");
    emit goRightSignal();
    this->mutex.lock();
    this->finished.wait(&(this->mutex));
    return this->target->returnValue;
}

bool Enemy::stopMove()
{
    qDebug("stopMove");
    emit stopMoveSignal();
    this->mutex.lock();
    this->finished.wait(&(this->mutex));
    return this->target->returnValue;
}

bool Enemy::forward(){
    emit forwardSignal();
}

bool Enemy::back(){
    emit backSignal();
}

bool Enemy::relativeLeft(){
    emit relativeLeftSignal();
}

bool Enemy::relativeRight(){
    emit relativeRightSignal();
}

bool Enemy::start()
{
    this->tree->runBehavior(this);
    qDebug("exit enemy");
    return true;
}
