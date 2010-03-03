#ifndef _BTCHARACTER_H_
#define _BTCHARACTER_H_

#include "btlib.h"
#include "btlib_export.h"

#include <QtCore/QObject>
#include <QtCore/QStack>
#include <QtCore/QList>
#include <QtCore/QQueue>
#include <QtCore/QMultiHash>
#include <QtCore/QPair>

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
	void stopParallelExecution(btNode * currentNode, QStack<btNode*>* parentStack);
	void clearExecution();
	
	btNode* m_behaviortree;
	
	//used for scheduler exectution
	QQueue<btNode::status> m_nodesStatusQueue;
	QQueue<QPair<QStack<btNode*>*, QStack<btNode*>*> > m_currentNodeStackQueue;
	QQueue<QStack<int> > m_currentChildStackQueue;
	
	//used for probselectors
	QHash<QStack<btNode*>*, QStack<QList<ProbNode*> > > m_visitedProbChildrenHash;
	
	//used for parallels
	QMultiHash<QStack<btNode*>*, QList<btNode::status>* > m_parallelNodeStatusHash;
};

#endif // _BTCHARACTER_H_
