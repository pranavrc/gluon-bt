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
	m_currentNodeStack.push(m_behaviortree);
	m_currentChildStack.push(0);
}

void btCharacter::think()
{
	btProbSelectorNode * probSelector = NULL;
	btParallelNode * parallel = NULL;
	btNode* currentNode = m_currentNodeStack.top();
	currentNode->setCurrentChildIndex(m_currentChildIndex);
	currentNode->setCurrentChildStatus(m_nodeStatus);
	currentNode->setParentNode(m_currentParent);
	
	if (QString(currentNode->metaObject()->className()) == "btProbSelectorNode")
	{
		probSelector = qobject_cast<btProbSelectorNode*>(currentNode);
		probSelector->setVisitedProbNodes(m_visitedProbChildren);
	}
	else if (QString(currentNode->metaObject()->className()) == "btParallelNode")
	{
		parallel = qobject_cast<btParallelNode*>(currentNode);
	}
	
	qDebug() <<"node " <<currentNode->name();
	/*if(m_currentParent != NULL)
		qDebug() <<"parent " <<m_currentParent->name();*/
	
	m_nodeStatus = currentNode->run(this);
	
	switch (m_nodeStatus)
	{
		case btNode::RunningChild:
			m_currentNodeStack.push(currentNode->currentChild());
			m_currentChildStack.push(currentNode->currentChildIndex());
			m_currentChildIndex = 0;
			m_currentParent = currentNode;
			m_nodeStatus = btNode::None;
			
			if(probSelector)
			{
				m_visitedProbChildrenStack.push(probSelector->visitedProbNodes());
				m_visitedProbChildren = QList<ProbNode*>();
			}
			break;
		case btNode::Failed:
		case btNode::Succeeded:
			if(m_currentNodeStack.top() != m_behaviortree)
			{
				m_currentNodeStack.pop();
				m_currentChildIndex = m_currentChildStack.pop();
				
				if(m_currentNodeStack.count() == 1)
				{
					m_currentParent = m_currentNodeStack.top();
				}
				else
				{
					m_currentParent = m_currentNodeStack.value(m_currentNodeStack.count()-2);
				}
				
				if(QString(m_currentNodeStack.top()->metaObject()->className()) == "btProbSelectorNode")
				{
					m_visitedProbChildren = m_visitedProbChildrenStack.pop();
				}
				else
				{
					m_visitedProbChildren = QList<ProbNode*>();
				}

			}
			else
			{
				m_currentParent = NULL;
				m_currentChildIndex = m_currentChildStack.top();
				m_nodeStatus = btNode::None;
			}
			break;
		case btNode::Running:
			m_currentChildIndex = currentNode->currentChildIndex();
			if(probSelector)
			{
				m_visitedProbChildren = probSelector->visitedProbNodes();
			}
			break;
	}
}

#include "btcharacter.moc"
