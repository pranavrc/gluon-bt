#ifndef BTNODEFACTORY_H
#define BTNODEFACTORY_H

class btNodeFactory : public QObject, public btAbstractFactory {
        Q_OBJECT
    public:
        static btNodeFactory* instance(); //singleton

};

#endif // BTNODEFACTORY_H
