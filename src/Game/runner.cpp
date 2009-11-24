#include "runner.h"

Runner::Runner()
{
}

Runner::Runner(Enemy *target)
{
    this->target = target;
}

void Runner::run()
{
    qsrand(QDateTime::currentDateTime().toTime_t() - (int)QThread::currentThreadId());
    this->target->start();
}
