#ifndef _BTCHARACTER_H_
#define _BTCHARACTER_H_

#include "btlib.h"
#include "btlib_export.h"

#include <QtCore/QObject>
#include <QtCore/QStack>
#include <QtCore/QList>
#include <QtCore/QQueue>
#include <QtCore/QHash>
#include <QtCore/QMultiHash>

struct ProbNode;

class BT_LIB_EXPORT btCharacter : public QObject
{
    Q_OBJECT
public:
    btCharacter();
    ~btCharacter();
	
	void setBehaviorTree(btNode* behaviorTree);
	
	void think();
private:
	void stopParallelExecution(btNode * currentNode);
	
	btNode* m_behaviortree;
	
	btNode::status m_nodeStatus;
	QQueue<btNode::status> m_nodesStatusQueue;
	
	int m_currentChildIndex;
	
	QQueue<QStack<btNode*>* > m_currentNodeStackQueue;
	QStack<btNode*>* m_currentNodeStack;
	
	QStack<int> m_currentChildStack;
	QQueue<QStack<int> > m_currentChildStackQueue;
	
	//used for probselectors
	QHash<QStack<btNode*>*, QStack<QList<ProbNode*> > > m_visitedProbChildrenHash;
	
	//used for parallels
	QMultiHash<QStack<btNode*>*, QList<btNode::status>* > m_parallelNodeStatusHash;
};

#endif // _BTCHARACTER_H_
