#include "relativeforward.h"

#include <QDebug>
#include <QtCore/QThread>
#include <QtCore>
#include "enemy.h"

REGISTER_NODETYPE(relativeForward)

relativeForward::relativeForward()
{
    // init variables
}

bool relativeForward::run(btCharacter *self)
{
    qDebug() << "relativeForward::run()";
    return ((Enemy*)self)->forward();
}

