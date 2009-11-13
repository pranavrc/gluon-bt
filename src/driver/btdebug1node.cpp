#include "btdebug1node.h"

#include <QDebug>
#include <QThread>
#include <QTest>

REGISTER_NODETYPE(btDebug1Node)

btDebug1Node::btDebug1Node()
{
    // init variables
}

bool btDebug1Node::run()
{
    for(int i = 0; i < 10;i++ ){
        qDebug() << QThread::currentThreadId() << "debug 1 behavior run";
        QTest::qSleep(500);
    }
    return false;
}

#include "btdebug1node.moc"
