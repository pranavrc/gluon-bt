#ifndef WORKER_H
#define WORKER_H

#include <QThread>
#include "btparallelnode.h"

class Worker : public QThread
{
    Q_OBJECT
public:
    Worker(btNode* node,btParallelNode* parent);
    Worker(){}
    void run();
    void setSelf(btCharacter *self);
    bool value;
    Worker* copy();
private:
    btParallelNode *parent;
    btCharacter *self;
    btNode* node;
};

#endif // WORKER_H
