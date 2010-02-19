#ifndef _BTCHARACTER_H_
#define _BTCHARACTER_H_

#include "btlib_export.h"

#include <QtCore/QObject>
#include <QtCore/QStack>

#include "btlib.h"

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
	
	QStack<btNode*> m_currentNode;
	QStack<int> m_currentChild;
	QStack<btNode*> m_parallelExecution;
};

#endif // _BTCHARACTER_H_
