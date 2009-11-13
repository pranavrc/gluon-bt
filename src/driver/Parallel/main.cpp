#include <QtCore/QCoreApplication>
#include "worker.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    Worker *w1 = new Worker(NULL);
    Worker *w2 = new Worker(w1);

    w1->start();
    w2->start();

    return a.exec();
}
