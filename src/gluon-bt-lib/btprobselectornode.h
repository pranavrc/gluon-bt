#ifndef BTPROBSELECTORNODE_H
#define BTPROBSELECTORNODE_H

#include <QObject>

#include "statnode.h"
#include "btlib.h"


class BT_LIB_EXPORT btProbSelectorNode : public btNode
{
    Q_OBJECT
    
public:
    Q_INVOKABLE btProbSelectorNode();
	btNode::status run(btCharacter *self);
    void appendingChild(int index);
    void removingChild(int index);
    void childrenAdded();
	void resetVisitedNodes();
	
private:
    QList<StatNode*> m_probStats;
	float m_currentScale;
	float m_currentStart;
};

#endif //BTPROBSELECTORNODE_H
