#include "relativeleft.h"

#include <QDebug>
#include <QtCore/QThread>
#include <QtCore>
#include "enemy.h"

REGISTER_NODETYPE(relativeLeft)

relativeLeft::relativeLeft()
{
    // init variables
}

bool relativeLeft::run(btCharacter *self)
{
    qDebug() << "relativeLeft::run()";
    return ((Enemy*)self)->relativeLeft();
}

