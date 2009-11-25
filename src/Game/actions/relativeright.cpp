#include "relativeright.h"

#include <QDebug>
#include <QtCore/QThread>
#include <QtCore>
#include "enemy.h"

REGISTER_NODETYPE(relativeRight)

relativeRight::relativeRight()
{
    // init variables
}

bool relativeRight::run(btCharacter *self)
{
    qDebug() << "relativeRight::run()";
    return ((Enemy*)self)->relativeRight();
}

