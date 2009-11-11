#include "btblockernode.h"

#include <QDebug>

REGISTER_NODETYPE(btBlockerNode)

btBlockerNode::btBlockerNode()
{
    // init variables
}

bool btBlockerNode::run()
{
    qDebug() << "node blocked";
    return false;
}

#include "btblockernode.moc"
