#ifndef BTNODEFACTORY_H
#define BTNODEFACTORY_H

#include <QObject>
#include <QString>
#include "btAbstractFactory.h"

class btNodeTypeFactory : public QObject, public btAbstractFactory {
        Q_OBJECT
    public:
        static btNodeTypeFactory* instance(); //singleton
        virtual btNodeType* newNodeType(QString classname);
    private:
        btNodeTypeFactory() {}

};

#endif // BTNODEFACTORY_H
