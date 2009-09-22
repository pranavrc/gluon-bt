#ifndef BTNODEFACTORY_H
#define BTNODEFACTORY_H

#include <QObject>
#include <QString>
#include "btfactory.h"
#include "btselectornode.h"

class btNodeTypeFactory : public QObject, public btAbstractFactory {
        Q_OBJECT
    public:
        static btNodeTypeFactory* instance(); //singleton
        virtual btNodeType* newObject(QString classname);
    private:
        btNodeTypeFactory() {}

};

#endif // BTNODEFACTORY_H
