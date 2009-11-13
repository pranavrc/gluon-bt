#ifndef WORKER_H
#define WORKER_H

#include <QThread>

class Worker : public QThread
{
public:
    Worker(Worker* w);
    void run();
private:
    Worker* w;
};

#endif // WORKER_H
