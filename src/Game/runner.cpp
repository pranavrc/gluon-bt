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
    qDebug("runner");
    qsrand(QDateTime::currentDateTime().toTime_t() - 234);//(int)QThread::currentThreadId());
    this->target->start();
}

Enemy* Runner::getTarget()
{
    return target;
}

#include "runner.moc"
