#include "go_up.h"

#include <QDebug>
#include <QtCore/QThread>
#include <QtCore>
#include "enemy.h"

REGISTER_NODETYPE(goUpNode)

goUpNode::goUpNode()
{
    // init variables
}

bool goUpNode::run(btCharacter *self)
{
    qDebug() << "goUpNode::run()";
    bool value = ((Enemy*)self)->goUp();
    ((Enemy*)self)->mutex.lock();
    ((Enemy*)self)->finished.wait(&(((Enemy*)self)->mutex));
    return value;
}

