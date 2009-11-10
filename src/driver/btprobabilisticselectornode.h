#ifndef BTPROBSELECTORNODE_H
#define BTPROBSELECTORNODE_H

#include <QObject>

#include "statnode.h"
#include "../gluon-bt-lib/btlib.h"


class btProbSelectorNode : public btNodeType
{
    Q_OBJECT
    
public:
    Q_INVOKABLE btProbSelectorNode();
    bool run();
    void appendingChild(int index);
    void removingChild(int index);
    void childrenAdded();

private:
    QList<StatNode> probStats;
};

#endif //BTPROBSELECTORNODE_H
