#include "btdebug1node.h"

#include <QDebug>

REGISTER_NODETYPE(btDebug1Node)

btDebug1Node::btDebug1Node()
{
    // init variables
}

bool btDebug1Node::run()
{
    qDebug() << "debug 1 behavior run";
    return true;
}

#include "btdebug1node.moc"
