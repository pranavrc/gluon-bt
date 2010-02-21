#ifndef BTPARALLELNODE_H
#define BTPARALLELNODE_H

#include "btlib.h"

#include <QtCore/QObject>
#include <QtCore/QStack>
#include <QtCore/QQueue>
#include <QtCore/QHash>

class btParallelNode : public btNode
{
    Q_OBJECT
	
public:
    Q_INVOKABLE btParallelNode();
	btNode::status run(btCharacter *self);
	
	void appendingChild(int index);
	void removingChild(int index);
	void childrenAdded();
	
	//QQueue<QStack<btNode*> > parallelChildren();
	//QQueue<QStack<int> > parallelChildrenIndex();
	
	QList<QStack<btNode*> > parallelChildren();
	QList<QStack<int> > parallelChildrenIndex();
	
	btNode::status conditionsFulfilled();
	
	void resetRunningNodesStatus();
	QList<btNode::status> runningNodesStatus();
	void setRunningNodesStatus(QList<btNode::status> nodeStatus);
	QList<QStack<btNode*> > runningNodesParents();
	
	int childNodeIndex(btNode* childNode);
private:
	QList<btNode*> m_runningNodes;
	QList<int> m_runningNodesIndexes;
	QList<btNode::status> m_runningNodesStatus;
	QList<btNode::status> m_conditionStatus;
	QList<QStack<btNode*> > m_childNodes;
	QList<QStack<int> > m_childNodesIndex;
	QList<QStack<btNode*> > m_parents;
	QHash<btNode*, int> m_nodesIndex;
};


#endif // BTPARALLELNODE_H
