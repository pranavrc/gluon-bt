#include "btdebugnode.h"

#include <QDebug>
#include <QThread>

REGISTER_NODETYPE(btDebugNode)

btDebugNode::btDebugNode()
{
    // init variables
}

bool btDebugNode::run(btCharacter *self)
{ 
    qDebug() << " says " << property("message").toString();
    return true;
}

#include "btdebugnode.moc"
