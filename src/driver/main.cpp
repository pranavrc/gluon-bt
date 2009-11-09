#include <QtGui/QApplication>
#include "driver.h"
#include "../gluon-bt-lib/btlib.h"
#include <QDebug>
#include <QLibrary>

int main(int argc, char** argv)
{
    QCoreApplication app(argc, argv);
    //btBrain *brain = new btBrain();
    btNodeType *node = new btNodeType();
    node->setClassName("Hej");
    qDebug() << node->className();




    return app.exec();
}
