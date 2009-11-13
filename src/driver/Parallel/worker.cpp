#include "worker.h"
#include <QDebug>

Worker::Worker(Worker* w)
{
    this->w = w;
}

void Worker::run()
{
    for(int count=0;count<20;count++) {
        sleep(1);
        if((w != NULL) && count == 10){
            qDebug() << "Behaviors Terminated";
            w->terminate();
            w->wait();
            terminate();

        }
        qDebug() << "Ping! from: " << QThread::currentThreadId();
    }
}
