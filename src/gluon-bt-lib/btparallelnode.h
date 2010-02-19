#ifndef BTPARALLELNODE_H
#define BTPARALLELNODE_H

#include "btlib.h"

#include <QtCore/QObject>
#include <QtCore/QList>

class btParallelNode : public btNode
{
    Q_OBJECT
	
public:
    Q_INVOKABLE btParallelNode();
	btNode::status run(btCharacter *self);
    void appendingChild(int index);
    void removingChild(int index);
    void childrenAdded();
};


#endif // BTPARALLELNODE_H
