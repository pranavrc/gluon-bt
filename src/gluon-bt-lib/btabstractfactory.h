#ifndef BTABSTRACTFACTORY_H
#define BTABSTRACTFACTORY_H

#include <QObject>
#include <QString>
#include "btnodetype.h"

class btAbstractFactory{
    public:
        virtual btNodeType* newObject (QString classname) = 0;
        virtual ~AbstractFactory() {}
};

#endif // BTABSTRACTFACTORY_H
