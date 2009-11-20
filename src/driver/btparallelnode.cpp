#include "btparallelnode.h"
#include "worker.h"

#include <QDebug>

REGISTER_NODETYPE(btParallelNode)

btParallelNode::btParallelNode()
{
    // init variables
}

bool btParallelNode::run(btCharacter *self)
{
    qDebug() << "Parallel Execution Started";
    foreach(Worker* w,workers){
        w->start();
    }
    foreach(Worker* w,workers){
        w->wait();
    }

    return decide();
}

void btParallelNode::appendingChild(int index)
{
    Worker *w = new Worker(parentNode()->child(index));
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

#include "btparallelnode.moc"
