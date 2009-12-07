#include "worker.h"
#include <QDebug>
#include <QDateTime>
#include "enemy.h"

Worker::Worker(btNode* node,btParallelNode* parent)
{
    this->parent = parent;
    this->node = node;
}

void Worker::setSelf(btCharacter *self)
{
    qDebug() << "set self";
    this->self = self;
}

void Worker::run()
{
    qDebug() << "worker run";
    qsrand(QDateTime::currentDateTime().toTime_t() - (int)QThread::currentThreadId());
    value = node->runBehavior(this->self);
    // this is a hack, this does not work
    foreach(Worker* worker,parent->workers){
        qDebug("terminating threads");
        if(worker != this){
            worker->node->type()->setStopFlag(true);
            //((Enemy*)self)->mutex.unlock();
            ((Enemy*)self)->finished.wakeAll();
           // ((Enemy*)self)->eventCond.wakeAll();
        }
    }
    qDebug() << "value: " << value;
}
