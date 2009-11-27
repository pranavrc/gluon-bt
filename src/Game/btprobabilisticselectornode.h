#ifndef BTPROBSELECTORNODE_H
#define BTPROBSELECTORNODE_H

#include <QObject>

#include "statnode.h"
#include "../gluon-bt-lib/btlib.h"
#include "enemy.h"


class btProbSelectorNode : public btNodeType
{
    Q_OBJECT
    
public:
    Q_INVOKABLE btProbSelectorNode();
    bool run(btCharacter *self);
    void appendingChild(int index);
    void removingChild(int index);
    void childrenAdded();
    QList<StatNode*> probStats; // lav om til property

};

#endif //BTPROBSELECTORNODE_H
