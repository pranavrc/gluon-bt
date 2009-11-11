#include "btdebug2node.h"

#include <QDebug>

REGISTER_NODETYPE(btDebug2Node)

btDebug2Node::btDebug2Node()
{
    // init variables
}

bool btDebug2Node::run()
{
    qDebug() << "debug 2 behavior run";
    return true;
}

#include "btdebug2node.moc"
