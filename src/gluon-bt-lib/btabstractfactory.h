#ifndef BTABSTRACTFACTORY_H
#define BTABSTRACTFACTORY_H

#include <QString>
#include "btnodetype.h"

class btAbstractFactory{
    public:
        virtual btNodeType* newObject (QString classname) = 0;
        virtual ~btAbstractFactory() {}
};

#endif // BTABSTRACTFACTORY_H
