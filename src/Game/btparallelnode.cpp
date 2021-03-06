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
    //qDebug() << "Parallel Execution Started";
    QList<Worker*> workerList;
    foreach(Worker* w,workers){
       // qDebug() << "First worker";
        //w->terminate();
        workerList.append(w->copy());
        workerList[workerList.count()-1]->setSelf(self);
//        w->setSelf(self);
  //      w->start();
        //workerList[workerList.count()-1]->value = true; // does this fix it -- morten
        workerList[workerList.count()-1]->start();

    }

    foreach(Worker* w,workerList){
        w->wait(60000); //1 min
        qDebug() << "thread stopped " << ((Enemy*)self)->name();
    }
qDebug() << "parallel done " << ((Enemy*)self)->name();
    ((Enemy*)self)->finished.wakeAll();
    
    bool result = decide(workerList);
    
    /*foreach(Worker* w,workerList)
    {
        w->terminate();
    }*/
    
    qDeleteAll(workerList);
    
    return result;
}

void btParallelNode::appendingChild(int index)
{
    //qDebug() << "append worker";
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

bool btParallelNode::decide(QList<Worker*> workList)
{
    // make sure to expose this choice in the editor
    /*foreach(Worker* w,workers){
        if(w->value == false){
            return false;
        }
    }
    return true;*/

    foreach(Worker* w,workList){
        qDebug() << "w: " << w->value;
        if(w->value == true){
            return true;
        }
    }
    return false;
}

#include "btparallelnode.moc"

