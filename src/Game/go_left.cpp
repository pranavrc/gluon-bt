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
   // qDebug() << "goLeftNode::run()";
    qDebug() <<"left "<< ((Enemy*)self)->name();
    return ((Enemy*)self)->goLeft();
}

#include "go_left.moc"
