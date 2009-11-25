#include "relativeback.h"

#include <QDebug>
#include <QtCore/QThread>
#include <QtCore>
#include "enemy.h"

REGISTER_NODETYPE(relativeBack)

relativeBack::relativeBack()
{
    // init variables
}

bool relativeBack::run(btCharacter *self)
{
    qDebug() << "relativeBack::run()";
    return ((Enemy*)self)->back();
}

