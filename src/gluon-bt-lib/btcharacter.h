#ifndef _BTCHARACTER_H_
#define _BTCHARACTER_H_

#include "btlib.h"
#include "btlib_export.h"

#include <QtCore/QObject>
#include <QtCore/QStack>

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
	btNode::status m_nodeStatus;
	int m_currentChildIndex;
	QList<ProbNode*> m_visitedProbChildren;
	
	QStack<btNode*> m_currentNodeStack;
	QStack<int> m_currentChildStack;
	QStack<btNode*> m_parallelExecutionStack;
	QStack<QList<ProbNode*> > m_visitedProbChildrenStack;
};

#endif // _BTCHARACTER_H_
