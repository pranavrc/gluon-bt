#include "go_up.h"

#include <QDebug>
#include <QtCore/QThread>
#include "enemy.h"

REGISTER_NODETYPE(goUpNode)

goUpNode::goUpNode()
{
    // init variables
}

bool goUpNode::run(btCharacter *self)
{
    qDebug() << "goUpNode::run()";
    ((Enemy*)self)->mutex.lock();
    //((Enemy*)self)->finished.wait();
    return ((Enemy*)self)->goUp();
}

