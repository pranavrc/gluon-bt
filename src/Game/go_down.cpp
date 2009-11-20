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
    bool value = ((Enemy*)self)->goDown();
    ((Enemy*)self)->mutex.lock();
    ((Enemy*)self)->finished.wait(&(((Enemy*)self)->mutex));
    return value;
}
