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
	//currentNode->setCurrentChildIndex(m_currentchild.top());
	qDebug() << m_currentNode.count();
	
	m_nodeStatus = currentNode->run(this);
#warning remember to set the child status again :)
	switch (m_nodeStatus)
	{
		case btNode::RunningChild:
			//getting child for execusing in next tick.
			//m_currentNode = m_currentNode->currentChild();
			m_currentNode.push(currentNode->currentChild());
			m_currentChild.push(currentNode->currentChildIndex());
			break;
		case btNode::Failed:
		case btNode::Succeeded:
			//resetting current child
			//currentNode->setCurrentChildIndex(0);
			//currentNode->setCurrentChildStatus(btNode::None);
			//aquiring the parent
			//m_currentNode = m_currentNode->parentNode();
			if(m_currentNode.top() != m_behaviortree)
			{
				m_currentNode.pop();
				m_currentChildIndex = m_currentChild.pop();
			}
			//setting the childstatus of the parent node
			//currentNode->setCurrentChildStatus(m_nodeStatus);
			break;
	}
}

#include "btcharacter.moc"
