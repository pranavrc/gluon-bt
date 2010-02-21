#include "btcharacter.h"

#include <QtCore/QDebug>

btCharacter::btCharacter()
{
	m_nodesStatusQueue.enqueue(btNode::None);
	m_currentChildIndex = 0;
	m_currentParentsStack.push(NULL);
	m_currentParentsQueue.enqueue(m_currentParentsStack);
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
	
	m_currentChildStackQueue.enqueue(m_currentChildStack);
	m_currentNodeStackQueue.enqueue(m_currentNodeStack);
}

void btCharacter::think()
{
	btProbSelectorNode * probSelector = NULL;
	btParallelNode * parallel = NULL;
	
	m_currentNodeStack = m_currentNodeStackQueue.dequeue();
	m_currentChildStack = m_currentChildStackQueue.dequeue();
	m_nodeStatus = m_nodesStatusQueue.dequeue();
	m_currentParentsStack = m_currentParentsQueue.dequeue();
	
	btNode* currentNode = m_currentNodeStack.top();
	
	if (QString(currentNode->metaObject()->className()) == "btProbSelectorNode")
	{
		probSelector = qobject_cast<btProbSelectorNode*>(currentNode);
		probSelector->setVisitedProbNodes(m_visitedProbChildren);
	}
	else if (QString(currentNode->metaObject()->className()) == "btParallelNode")
	{
		parallel = qobject_cast<btParallelNode*>(currentNode);
		
		if(m_nodeStatus == btNode::None)
		{
			m_currentNodeStackQueue.append(parallel->parallelChildren());
			m_currentChildStackQueue.append(parallel->parallelChildrenIndex());
			m_nodesStatusQueue.append(parallel->runningNodesStatus());
			m_currentParentsQueue.append(parallel->runningNodesParents());
			m_nodeStatus = btNode::RunningChild;
		}
		
		m_currentNodeStackQueue.enqueue(m_currentNodeStack);
		m_currentChildStack.push(m_currentChildIndex);
		m_currentChildStackQueue.enqueue(m_currentChildStack);
		
		m_currentNodeStack = m_currentNodeStackQueue.dequeue();
		m_currentChildStack = m_currentChildStackQueue.dequeue();
		
		m_nodesStatusQueue.enqueue(m_nodeStatus);
		m_nodeStatus = m_nodesStatusQueue.dequeue();
		
		m_currentParentsQueue.enqueue(m_currentParentsStack);
		m_currentParentsStack = m_currentParentsQueue.dequeue();
		
		currentNode = m_currentNodeStack.top();
		m_currentParent = m_currentParentsStack.top();
		if(m_currentChildStack.count() > 0)
		{
			m_currentChildIndex = m_currentChildStack.pop();
		}
		else 
		{
			m_currentChildIndex = 0;
		}
	}	
	
	currentNode->setCurrentChildIndex(m_currentChildIndex);
	currentNode->setCurrentChildStatus(m_nodeStatus);
	currentNode->setParentNode(m_currentParent);
	
	qDebug() <<"node " <<currentNode->name();
	/*if(m_currentParent != NULL)
	 qDebug() <<"parent " <<m_currentParent->name();*/
	
	m_nodeStatus = currentNode->run(this);
	
	switch (m_nodeStatus)
	{
		case btNode::RunningChild:
			m_currentNodeStack.push(currentNode->currentChild());
			m_currentChildStack.push(currentNode->currentChildIndex());
			
			m_currentNodeStackQueue.enqueue(m_currentNodeStack);
			m_currentChildStackQueue.enqueue(m_currentChildStack);
			
			m_nodesStatusQueue.enqueue(btNode::None);
			
			m_currentChildIndex = 0;
			m_currentParentsStack.push(currentNode);
			m_currentParentsQueue.enqueue(m_currentParentsStack);
			
			if(probSelector)
			{
				m_visitedProbChildrenStack.push(probSelector->visitedProbNodes());
				m_visitedProbChildren = QList<ProbNode*>();
			}
			
			break;
		case btNode::Failed:
		case btNode::Succeeded:
			if(m_currentNodeStack.count() > 1)
			{	
				m_currentNodeStack.pop();
				if(m_currentChildStack.count() > 0)
				{
					m_currentChildIndex = m_currentChildStack.pop();
				}
				else 
				{
					m_currentChildIndex = 0;
				}
				
				if(m_currentParentsStack.count() > 1)
				{
					m_currentParent = m_currentParentsStack.pop();
				}
				else 
				{
					m_currentParent = m_currentParentsStack.top();
				}
				
				if(m_currentNodeStack.count() > 0 && QString(m_currentParent->metaObject()->className()) == "btProbSelectorNode")
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
				
				m_currentParent = m_currentParentsStack.top();
				if(m_currentChildStack.count() > 0)
				{
					m_currentChildIndex = m_currentChildStack.top();
				}
				else
				{
					m_currentChildStack.push(0);
				}
				
				if(currentNode == m_behaviortree)
					m_nodeStatus = btNode::None;
			}	
			
			if(m_currentParent->metaObject()->className() == "btParallelNode")
			{
				parallel = qobject_cast<btParallelNode*>(m_currentParent);
				
			}
			else//*/
			{
				m_currentNodeStackQueue.enqueue(m_currentNodeStack);
				m_currentChildStackQueue.enqueue(m_currentChildStack);
				m_nodesStatusQueue.enqueue(m_nodeStatus);
				m_currentParentsQueue.enqueue(m_currentParentsStack);
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
