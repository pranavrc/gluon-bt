#include "btparallelnode.h"

#include <QtCore/QDebug>

REGISTER_NODETYPE(btParallelNode)

btParallelNode::btParallelNode()
{
    // init variables
}

btNode::status btParallelNode::run(btCharacter *self)
{
    //qDebug() << "Parallel Execution Started";
   /* QList<Worker*> workerList;
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
    }
    
    qDeleteAll(workerList);*/
    
    return Succeeded;
}

void btParallelNode::appendingChild(int index)
{
    //qDebug() << "append worker";
    /*Worker *w = new Worker(parentNode()->child(index),this);
    workers.insert(index,w);*/
}

void btParallelNode::removingChild(int index)
{
	//workers.removeAt(index);
}

void btParallelNode::childrenAdded()
{

}

#include "btparallelnode.moc"

