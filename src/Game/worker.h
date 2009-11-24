#ifndef WORKER_H
#define WORKER_H

#include <QThread>
#include "btparallelnode.h"

class Worker : public QThread
{
public:
    Worker(btNode* node);
    Worker(){}
    void run();
    void setSelf(btCharacter *self);
    bool value;
private:
    btCharacter *self;
    btNode* node;
};

#endif // WORKER_H
