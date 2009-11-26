#include "btparallelnode.h"
#include "worker.h"
#include "enemy.h"

#include <QDebug>

REGISTER_NODETYPE(btParallelNode)

btParallelNode::btParallelNode()
{
    // init variables
}

void btParallelNode::workerDone()
{
    qDebug("worker done");
}

bool btParallelNode::run(btCharacter *self)
{
    qDebug() << "Parallel Execution Started";
    foreach(Worker* w,workers){
        qDebug() << "First worker";
        w->setSelf(self);
        w->start();

    }

    foreach(Worker* w,workers){
        w->wait();
        qDebug() << "thread stopped";
    }
qDebug("parallel done");
    return decide();
}

void btParallelNode::appendingChild(int index)
{
    qDebug() << "append worker";
    Worker *w = new Worker(parentNode()->child(index),this);
    workers.insert(index,w);
}

void btParallelNode::removingChild(int index)
{
    workers.removeAt(index);
}

void btParallelNode::childrenAdded()
{

}

bool btParallelNode::decide()
{
    foreach(Worker* w,workers){
        if(w->value == false){
            return false;
        }
    }
    return true;
}
