#ifndef BTNODEFACTORY_H
#define BTNODEFACTORY_H

class btNodeTypeFactory : public QObject, public btAbstractFactory {
        Q_OBJECT
    public:
        static btNodeTypeFactory* instance(); //singleton
        virtual btNodeType*
};

#endif // BTNODEFACTORY_H
