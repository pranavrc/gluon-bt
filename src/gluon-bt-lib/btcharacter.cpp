#include "btcharacter.h"

#include <QtCore/QDebug>

btCharacter::btCharacter()
{
	m_nodeStatus = btNode::None;
	m_currentChildIndex = 0;
	m_currentParent = NULL;
}

btCharacter::~btCharacter()
{

}

void btCharacter::setBehaviorTree(btNode* behaviorTree)
{
	//m_behaviortree = m_currentNode = behaviorTree;
	m_behaviortree = behaviorTree;
	m_currentNode.push(m_behaviortree);
	m_currentChild.push(0);
}

void btCharacter::think()
{
	btNode* currentNode = m_currentNode.top();
	currentNode->setCurrentChildIndex(m_currentChildIndex);
	currentNode->setCurrentChildStatus(m_nodeStatus);
	currentNode->setParentNode(m_currentParent);
	
	/*qDebug() <<"node " <<currentNode->name();
	if(m_currentParent != NULL)
		qDebug() <<"parent " <<m_currentParent->name();*/
	
	m_nodeStatus = currentNode->run(this);
	
	switch (m_nodeStatus)
	{
		case btNode::RunningChild:
			m_currentNode.push(currentNode->currentChild());
			m_currentChild.push(currentNode->currentChildIndex());
			m_currentChildIndex = 0;
			m_currentParent = currentNode;
			m_nodeStatus = btNode::None;
			break;
		case btNode::Failed:
		case btNode::Succeeded:
			if(m_currentNode.top() != m_behaviortree)
			{
				m_currentNode.pop();
				m_currentChildIndex = m_currentChild.pop();
				
				if(m_currentNode.count() == 1)
				{
					m_currentParent = m_currentNode.top();
				}
				else
				{
					m_currentParent = m_currentNode.value(m_currentNode.count()-2);
				}
			}
			else
			{
				m_currentParent = NULL;
				m_currentChildIndex = m_currentChild.top();
				m_nodeStatus = btNode::None;
			}
			break;
		case btNode::Running:
			m_currentChildIndex = currentNode->currentChildIndex();
			break;
	}
}

#include "btcharacter.moc"
