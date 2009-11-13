#include "btdebug2node.h"

#include <QDebug>
#include <QThread>
#include <QTest>

REGISTER_NODETYPE(btDebug2Node)

btDebug2Node::btDebug2Node()
{
    // init variables
}

bool btDebug2Node::run()
{
    for(int i = 0; i < 10;i++ ){
        qDebug() << QThread::currentThreadId() << "debug 2 behavior run";
        QTest::qSleep(500);
    }
    return true;
}

#include "btdebug2node.moc"
