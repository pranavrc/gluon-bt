#include "changecolor.h"

#include <QDebug>
#include <QtCore/QThread>
#include <QtCore>
#include "enemy.h"
#include "agent.h"
#include <QBrush>
#include <QColor>

REGISTER_NODETYPE(changeColor)

changeColor::changeColor()
{
    // init variables
}

bool changeColor::run(btCharacter *self)
{
    qDebug() << "changeColor::run()";
    ((Enemy*)self)->target->setBrush(QBrush(QColor(property("color").toString())));
    return true;
}

