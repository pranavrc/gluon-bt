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
	//m_behaviortree = m_currentNode = behaviorTree;
	m_behaviortree = behaviorTree;
	m_currentNode.push(m_behaviortree);
}

void btCharacter::think()
{
	btNode* currentNode = m_currentNode.top();
	currentNode->setCurrentChildIndex(m_currentchild.top());
	
	m_nodeStatus = currentNode->run(this);
#warning remember to set the child status again :)
	switch (m_nodeStatus)
	{
		case btNode::RunningChild:
			m_currentNode.push(currentNode->currentChild());
			m_currentChild.push(currentNode->currentChildIndex());
			break;
		case btNode::Failed:
		case btNode::Succeeded:
			if(m_currentNode.top() != m_behaviortree)
			{
				m_currentNode.pop();
				m_currentChildIndex = m_currentChild.pop();
			}
			break;
	}
}

#include "btcharacter.moc"
