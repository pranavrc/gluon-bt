#include "worker.h"
#include <QDebug>
#include <QDateTime>

Worker::Worker(btNode* node)
{
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
    qDebug() << "value: " << value;
}
