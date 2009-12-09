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
    this->target->setEventMutex(&(this->eventMutex));
    this->target->setEventCondition(&(this->eventCond));
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
    QObject::connect(this, SIGNAL(moveCloserSignal()),
                     this->target, SLOT(moveCloser()));
    QObject::connect(this, SIGNAL(collisionSignal()),
                     this->target, SLOT(collision()));
}

bool Enemy::goDown()
{
    qDebug("enemyDown");
   this->mutex.lock();
    emit goDownSignal();
    //this->mutex.lock();
    this->finished.wait(&(this->mutex));
    qDebug("finished waiting");
       this->mutex.unlock();
       qDebug("unlocked now");
    return this->target->returnValue;
}

bool Enemy::goUp()
{
    qDebug("enemyUp");
    this->mutex.lock();
    emit goUpSignal();
    //this->mutex.lock();
    this->finished.wait(&(this->mutex));
    qDebug("finished waiting");
      this->mutex.unlock();
      qDebug("unlocked now");
    return this->target->returnValue;
}

bool Enemy::goLeft()
{
    qDebug("enemyLeft");
   this->mutex.lock();
    emit goLeftSignal();
    //this->mutex.lock();
    this->finished.wait(&(this->mutex));
    qDebug("finished waiting");
        this->mutex.unlock();
        qDebug("unlocked now");
    return this->target->returnValue;
}

bool Enemy::goRight()
{
    qDebug("enemyRight");
    this->mutex.lock();
    emit goRightSignal();
    //this->mutex.lock();
    this->finished.wait(&(this->mutex));
    qDebug("finished waiting");
      this->mutex.unlock();
      qDebug("unlocked now");
    return this->target->returnValue;
}

bool Enemy::stopMove()
{
    qDebug("stopMove");
  this->mutex.lock();
    emit stopMoveSignal();
    //this->mutex.lock();
    this->finished.wait(&(this->mutex));
    qDebug("finished waiting");
        this->mutex.unlock();
        qDebug("unlocked now");
    return this->target->returnValue;
}

bool Enemy::forward(){
    qDebug("about to lock");
    this->mutex.lock();
    emit forwardSignal();
    //    this->mutex.lock();
    this->finished.wait(&(this->mutex));
    qDebug("finished waiting");
       this->mutex.unlock();
       qDebug("unlocked now");
    return this->target->returnValue;
}

bool Enemy::back(){
    qDebug("about to lock");
    this->mutex.lock();
    emit backSignal();
     //   this->mutex.lock();
    this->finished.wait(&(this->mutex));
    qDebug("finished waiting");
      this->mutex.unlock();
      qDebug("unlocked now");
    return this->target->returnValue;
}

bool Enemy::relativeLeft(){
    qDebug("about to lock");
    this->mutex.lock();
    emit relativeLeftSignal();
    //    this->mutex.lock();
    this->finished.wait(&(this->mutex));
    qDebug("finished waiting");
     this->mutex.unlock();
     qDebug("unlocked now");
    return this->target->returnValue;
}

bool Enemy::relativeRight(){
    qDebug("about to lock");
   this->mutex.lock();
    emit relativeRightSignal();
    //    this->mutex.lock();
    this->finished.wait(&(this->mutex));
    qDebug("finished waiting");
    this->mutex.unlock();
    qDebug("unlocked now");
    return this->target->returnValue;
}

bool Enemy::collision(){
    qDebug("about to lock");
   //this->mutex.lock();
    emit collisionSignal();
    //    this->mutex.lock();
    //this->finished.wait(&(this->mutex));
    qDebug("finished waiting");
   // this->mutex.unlock();
    qDebug("unlocked now");
    return this->target->returnValue;
}


bool Enemy::start()
{
    this->tree->runBehavior(this);
    qDebug("exit enemy");
    return true;
}
