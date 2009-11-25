#include "btdebugnode.h"

#include <QDebug>
#include <QThread>
#include <QTest>

REGISTER_NODETYPE(btDebugNode)

btDebugNode::btDebugNode()
{
    // init variables
}

bool btDebugNode::run(btCharacter *self)
{ 
    QTest::qSleep(500);
    qDebug() << " says " << property("message").toString();
    return true;
}

