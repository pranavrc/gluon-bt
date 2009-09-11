#ifndef BTABSTRACTFACTORY_H
#define BTABSTRACTFACTORY_H

#include <QObject>
#include <QString>

class btAbstractFactory{
    public:
        virtual btnodetype* newObject (QString classname) = 0;
        virtual ~AbstractFactory() {}
};

#endif // BTABSTRACTFACTORY_H
