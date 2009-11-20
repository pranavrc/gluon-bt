#include "go_down.h"

#include <QDebug>
#include <QThread>
#include "enemy.h"

REGISTER_NODETYPE(goDownNode)

goDownNode::goDownNode()
{
    // init variables
}

bool goDownNode::run(btCharacter *self)
{
    qDebug() << "goDownNode::run()";
    return ((Enemy*)self)->goDown();
}
