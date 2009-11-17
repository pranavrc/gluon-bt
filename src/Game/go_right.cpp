#include "go_right.h"

#include <QDebug>
#include <QThread>
#include <QtTest/QTest>

REGISTER_NODETYPE(goRightNode)

goRightNode::goRightNode()
{
    // init variables
}

bool goRightNode::run()
{
    qDebug() << "right run";
    return false;
}
