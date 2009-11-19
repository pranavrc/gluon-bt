#include "go_right.h"

#include <QDebug>
#include <QThread>
#include "enemy.h"

REGISTER_NODETYPE(goRightNode)

goRightNode::goRightNode()
{
    // init variables
}

bool goRightNode::run(btCharacter *self)
{
    qDebug() << "goRightNode::run()";
    bool value = ((Enemy*)self)->goRight();
    ((Enemy*)self)->mutex.lock();
    ((Enemy*)self)->finished.wait(&(((Enemy*)self)->mutex));
    return value;
}
