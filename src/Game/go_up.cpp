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
    return ((Enemy*)self)->goUp();
}

