#include "worker.h"
#include <QDebug>

Worker::Worker(btNode* node)
{
    this->node = node;
}

void Worker::run()
{
    value = node->runBehavior();
}
