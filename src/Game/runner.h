#ifndef RUNNER_H
#define RUNNER_H

#include <QThread>
#include "enemy.h"

class Runner : public QThread
{
public:
    Runner();
    Runner(Enemy *target);
    void run();
private:
    Enemy* target;
};

#endif // RUNNER_H
