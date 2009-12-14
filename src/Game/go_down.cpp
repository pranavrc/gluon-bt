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
   // qDebug() << "goDownNode::run()";
    qDebug() <<"down " << ((Enemy*)self)->name();
    return ((Enemy*)self)->goDown();
}

#include "go_down.moc"
