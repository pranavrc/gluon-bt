#include "stopmove.h"

#include <QDebug>
#include <QtCore/QThread>
#include <QtCore>
#include "enemy.h"

REGISTER_NODETYPE(stopMove)

stopMove::stopMove()
{
    // init variables
}

bool stopMove::run(btCharacter *self)
{
    qDebug() << "stopMove::run()";
    return ((Enemy*)self)->stopMove();
}

