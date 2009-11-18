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
    qDebug() << property("message").toString();
    return true;
}

#include "btdebugnode.moc"
