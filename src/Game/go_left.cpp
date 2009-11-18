#include "go_left.h"

#include <QDebug>
#include <QThread>
#include <QtTest/QTest>

REGISTER_NODETYPE(goLeftNode)

goLeftNode::goLeftNode()
{
    // init variables
}

bool goLeftNode::run()
{
    qDebug() << "goLeftNode::run()";
    return self->goLeft();
}
