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
 //   qDebug() << "goUpNode::run()";
    qDebug()<<"up " << ((Enemy*)self)->name();
    return ((Enemy*)self)->goUp();
}

#include "go_up.moc"
