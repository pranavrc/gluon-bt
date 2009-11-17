#include "go_down.h"

#include <QDebug>
#include <QThread>
#include <QtTest/QTest>

REGISTER_NODETYPE(goDownNode)

goDownNode::goDownNode()
{
    // init variables
}

bool goDownNode::run()
{

    qDebug() << "down run";
    return false;
}
