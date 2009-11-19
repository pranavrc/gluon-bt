#include "go_left.h"

#include <QDebug>
#include <QThread>
#include "enemy.h"

REGISTER_NODETYPE(goLeftNode)

goLeftNode::goLeftNode()
{
    // init variables
}

bool goLeftNode::run(btCharacter *self)
{
    qDebug() << "goLeftNode::run()";
    bool value = ((Enemy*)self)->goLeft();
    ((Enemy*)self)->mutex.lock();
    ((Enemy*)self)->finished.wait(&(((Enemy*)self)->mutex));
    return value;
}

