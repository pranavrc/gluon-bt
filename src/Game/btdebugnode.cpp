#include "btdebugnode.h"

#include <QDebug>
#include <QThread>
#include "enemy.h"

REGISTER_NODETYPE(btDebugNode)

btDebugNode::btDebugNode()
{
    // init variables
}

bool btDebugNode::run(btCharacter *self)
{ 
    qDebug() << ((Enemy*)self)->name() << " says " << property("message").toString();
    return true;
}

#include "btdebugnode.moc"
