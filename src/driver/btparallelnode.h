#ifndef BTPARALLELNODE_H
#define BTPARALLELNODE_H

#include <QObject>

#include "../gluon-bt-lib/btlib.h"

#include <QList>

class Worker;

class btParallelNode : public btNodeType
{
    Q_OBJECT
    
public:
    Q_INVOKABLE btParallelNode();
    bool run(btCharacter *self);
    void appendingChild(int index);
    void removingChild(int index);
    void childrenAdded();
    virtual bool decide();
private:
    QList<Worker*> workers;
};


#endif // BTPARALLELNODE_H
