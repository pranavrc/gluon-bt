#include "go_up.h"

#include <QDebug>
#include <QtCore/QThread>
#include <QtTest/QTest>

REGISTER_NODETYPE(goUpNode)

goUpNode::goUpNode()
{
    // init variables
}

bool goUpNode::run()
{
    qDebug() << "up run";
    return false;
}

