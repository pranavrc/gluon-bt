#include "btcharacter.h"

#include <QtCore/QDebug>

btCharacter::btCharacter()
{
	m_nodeStatus = btNode::None;
}

btCharacter::~btCharacter()
{

}

void btCharacter::setBehaviorTree(btNode* behaviorTree)
{
	m_behaviortree = m_currentNode = behaviorTree;
}

void btCharacter::think()
{
	m_nodeStatus = m_currentNode->run(this);
	
	switch (m_nodeStatus)
	{
		case btNode::RunningChild:
			//getting child for execusing in next tick.
			m_currentNode = m_currentNode->currentChild();
			break;
		case btNode::Failed:
		case btNode::Succeeded:
			//resetting current child
			m_currentNode->setCurrentChildIndex(0);
			m_currentNode->setCurrentChildStatus(btNode::None);
			//aquiring the parent
			m_currentNode = m_currentNode->parentNode();
			//setting the childstatus of the parent node
			m_currentNode->setCurrentChildStatus(m_nodeStatus);
			break;
	}
}

#include "btcharacter.moc"
