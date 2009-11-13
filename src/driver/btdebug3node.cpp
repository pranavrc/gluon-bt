#include "btdebug3node.h"

#include <QDebug>
#include <QThread>
#include <QTest>

REGISTER_NODETYPE(btDebug3Node)

btDebug3Node::btDebug3Node()
{
    // init variables
}

bool btDebug3Node::run()
{
    for(int i = 0; i < 10;i++ ){
        qDebug() << QThread::currentThreadId() << "debug 3 behavior run";
        QTest::qSleep(500);
    }
    return true;
}

#include "btdebug3node.moc"
