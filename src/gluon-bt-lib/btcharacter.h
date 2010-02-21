#ifndef _BTCHARACTER_H_
#define _BTCHARACTER_H_

#include "btlib.h"
#include "btlib_export.h"

#include <QtCore/QObject>
#include <QtCore/QStack>
#include <QtCore/QList>
#include <QtCore/QQueue>
#include <QtCore/QHash>

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
	btNode* m_behaviortree;
	
	btNode* m_currentParent;
	QStack<btNode*> m_currentParentsStack;
	QQueue<QStack<btNode*> > m_currentParentsQueue;
	
	btNode::status m_nodeStatus;
	QQueue<btNode::status> m_nodesStatusQueue;
	
	int m_currentChildIndex;
	
	QList<ProbNode*> m_visitedProbChildren;
	
	QQueue<QStack<btNode*> > m_currentNodeStackQueue;
	QStack<btNode*> m_currentNodeStack;
	
	QStack<int> m_currentChildStack;
	QQueue<QStack<int> > m_currentChildStackQueue;
	
	//used for probselectors
	QStack<QList<ProbNode*> > m_visitedProbChildrenStack;
	
	//used for parallels
	QHash<btNode*, QStack<QList<btNode::status> > > m_parallelNodeStatusHash;
	QList<btNode::status> m_parallelNodeStatus;
};

#endif // _BTCHARACTER_H_
