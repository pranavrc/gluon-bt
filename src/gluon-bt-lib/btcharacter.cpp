#include "btcharacter.h"

#include <QtCore/QDebug>

btCharacter::btCharacter()
{
	m_nodesStatusQueue.enqueue(btNode::None);
	m_currentChildIndex = 0;
	//m_currentParentsStack.push(NULL);
	//m_currentParentsQueue.enqueue(m_currentParentsStack);
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
	btNode* m_currentParent = NULL;
	QStack<QList<ProbNode*> > visitedProbChildrenStack;

	m_currentNodeStack = m_currentNodeStackQueue.dequeue();
	m_currentChildStack = m_currentChildStackQueue.dequeue();
	m_nodeStatus = m_nodesStatusQueue.dequeue();
	
	btNode* currentNode = m_currentNodeStack.top();
	
	if(m_currentNodeStack.count() > 1)
	{
		m_currentParent = m_currentNodeStack.at(m_currentNodeStack.count() - 2);
	}

	
	if(m_currentChildStack.count() > 0)
	{
		m_currentChildIndex = m_currentChildStack.pop();
	}
	else 
	{
		m_currentChildIndex = 0;
	}
	
	if (QString(currentNode->metaObject()->className()) == "btProbSelectorNode")
	{
		probSelector = qobject_cast<btProbSelectorNode*>(currentNode);
		probSelector->setVisitedProbNodes(m_visitedProbChildren);
	}
	else if (QString(currentNode->metaObject()->className()) == "btParallelNode")
	{
		parallel = qobject_cast<btParallelNode*>(currentNode);
		qDebug() << parallel->name();		
		
		if(m_nodeStatus == btNode::None)
		{
			m_currentNodeStackQueue.append(parallel->parallelChildren());
			m_currentChildStackQueue.append(parallel->parallelChildrenIndex());
			m_nodesStatusQueue.append(parallel->runningNodesStatus());
			
			if(m_parallelNodeStatusHash.contains(parallel))
			{
				m_parallelNodeStatusHash[parallel].push(parallel->runningNodesStatus());
			}
			else
			{
				m_parallelNodeStatusHash[parallel] = QStack<QList<btNode::status> >();
				m_parallelNodeStatusHash[parallel].push(parallel->runningNodesStatus());
			}

			
			m_nodeStatus = btNode::Running;
		}
		parallel->setRunningNodesStatus(m_parallelNodeStatusHash[parallel].top());
		btNode::status conditionsFulfilled = parallel->conditionsFulfilled();

		if(conditionsFulfilled == btNode::Failed || conditionsFulfilled == btNode::Succeeded)
		{
			m_parallelNodeStatusHash[parallel].pop();
		}		
		
		m_nodeStatus = conditionsFulfilled;
	}	
	
	currentNode->setCurrentChildIndex(m_currentChildIndex);
	currentNode->setCurrentChildStatus(m_nodeStatus);
	currentNode->setParentNode(m_currentParent);
	
	qDebug() <<"node " <<currentNode->name();
	
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
				//m_currentParent = m_currentParentsStack.top();
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
			
			
#warning add such that it removes all children that are currently executed, check the with the first node in the stack and the parallel itself
			if(m_currentParent != NULL && QString(m_currentParent->metaObject()->className()) == "btParallelNode")
			{
				parallel = qobject_cast<btParallelNode*>(m_currentParent);
				m_parallelNodeStatus = m_parallelNodeStatusHash[m_currentParent].pop();
				m_parallelNodeStatus[parallel->childNodeIndex(currentNode)] = m_nodeStatus;
				m_parallelNodeStatusHash[m_currentParent].push(m_parallelNodeStatus);
			}
			else
			{
				m_currentNodeStackQueue.enqueue(m_currentNodeStack);
				m_currentChildStackQueue.enqueue(m_currentChildStack);
				m_nodesStatusQueue.enqueue(m_nodeStatus);
			}
			break;
		case btNode::Running:
			m_currentChildIndex = currentNode->currentChildIndex();
			
			m_currentNodeStackQueue.enqueue(m_currentNodeStack);
			m_currentChildStack.push(m_currentChildIndex);
			m_currentChildStackQueue.enqueue(m_currentChildStack);
			m_nodesStatusQueue.enqueue(m_nodeStatus);
			
			if(probSelector)
			{
				m_visitedProbChildren = probSelector->visitedProbNodes();
			}
			break;
	}
}

#include "btcharacter.moc"
