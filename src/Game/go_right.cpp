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
    return ((Enemy*)self)->goRight();
}

#include "go_right.moc"
