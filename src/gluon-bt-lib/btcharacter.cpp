#include "btcharacter.h"

#include <QtCore/QDebug>

btCharacter::btCharacter()
{
	m_nodesStatusQueue.enqueue(btNode::None);
	m_currentChildIndex = 0;
}

btCharacter::~btCharacter()
{
	
}

void btCharacter::setBehaviorTree(btNode* behaviorTree)
{
	m_behaviortree = behaviorTree;
	
	m_currentNodeStack = new QStack<btNode*>();
	m_currentNodeStack->push(m_behaviortree);
	m_currentChildStack.push(0);
	
	m_currentChildStackQueue.enqueue(m_currentChildStack);
	m_currentNodeStackQueue.enqueue(m_currentNodeStack);
}

void btCharacter::think()
{
	btProbSelectorNode * probSelector = NULL;
	btParallelNode * parallel = NULL;
	btNode* currentParent = NULL;
	QStack<QList<ProbNode*> > visitedProbChildrenStack;

	m_currentNodeStack = m_currentNodeStackQueue.dequeue();
	m_currentChildStack = m_currentChildStackQueue.dequeue();
	m_nodeStatus = m_nodesStatusQueue.dequeue();
	
	btNode* currentNode = m_currentNodeStack->top();
	
	if(m_currentNodeStack->count() > 1)
	{
		currentParent = m_currentNodeStack->at(m_currentNodeStack->count() - 2);
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
		
		if(m_visitedProbChildrenHash.contains(m_currentNodeStack))
		{
			probSelector->setVisitedProbNodes(m_visitedProbChildrenHash[m_currentNodeStack].pop());
		}
	}
	else if (QString(currentNode->metaObject()->className()) == "btParallelNode")
	{
		parallel = qobject_cast<btParallelNode*>(currentNode);
		if(m_nodeStatus == btNode::None)
		{			
			QList<btNode::status>* childStatus = new QList<btNode::status>();
			
			for(int i = 0; i < parallel->childCount(); i++)
			{
				QStack<btNode*>* newStack = new QStack<btNode*>();
				newStack->push(parallel);
				newStack->push(parallel->child(i));
				m_currentNodeStackQueue.enqueue(newStack);
				
				childStatus->append(btNode::None);
				m_nodesStatusQueue.enqueue(btNode::None);
				
				m_parallelNodeStatusHash.insert(newStack, childStatus);
				
				QStack<int> childStack = QStack<int>();
				childStack.push(0);
				m_currentChildStackQueue.append(childStack);
			}
			
			m_parallelNodeStatusHash.insert(m_currentNodeStack, childStatus);
			m_nodeStatus = btNode::Running;
		}
		
		parallel->setRunningNodesStatus(m_parallelNodeStatusHash.value(m_currentNodeStack));
		btNode::status conditionsFulfilled = parallel->conditionsFulfilled();
		
		m_nodeStatus = conditionsFulfilled;
	}	
	
	currentNode->setCurrentChildIndex(m_currentChildIndex);
	currentNode->setCurrentChildStatus(m_nodeStatus);
	currentNode->setParentNode(currentParent);
	
	m_nodeStatus = currentNode->run(this);
	
	switch (m_nodeStatus)
	{
		case btNode::RunningChild:
			m_currentNodeStack->push(currentNode->currentChild());
			m_currentChildStack.push(currentNode->currentChildIndex());
			
			m_currentNodeStackQueue.enqueue(m_currentNodeStack);
			m_currentChildStackQueue.enqueue(m_currentChildStack);
			
			m_nodesStatusQueue.enqueue(btNode::None);
			
			m_currentChildIndex = 0;
			
			if(probSelector)
			{
				m_visitedProbChildrenHash[m_currentNodeStack].push(probSelector->visitedProbNodes());
			}
			
			break;
		case btNode::Failed:
		case btNode::Succeeded:
			if(m_currentNodeStack->count() > 1)
			{	
				m_currentNodeStack->pop();
				if(m_currentChildStack.count() > 0)
				{
					m_currentChildIndex = m_currentChildStack.pop();
				}
				else 
				{
					m_currentChildIndex = 0;
				}
				
				/*if(m_currentNodeStack->count() > 0 && QString(currentParent->metaObject()->className()) == "btProbSelectorNode")
				{
					m_visitedProbChildren = m_visitedProbChildrenStack.pop();
				}
				else
				{
					m_visitedProbChildren = QList<ProbNode*>();
				}*/
			}
			else
			{				
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
			
			if(currentParent != NULL && QString(currentParent->metaObject()->className()) == "btParallelNode")
			{
				parallel = qobject_cast<btParallelNode*>(currentParent);
				QList<btNode::status>* m_parallelNodeStatus = m_parallelNodeStatusHash.value(m_currentNodeStack);
				m_parallelNodeStatus->replace(parallel->childNodeIndex(currentNode), m_nodeStatus);
				m_parallelNodeStatusHash.remove(m_currentNodeStack, m_parallelNodeStatus);
				
				if(m_parallelNodeStatusHash.count(m_currentNodeStack) > 0)
				{
					m_parallelNodeStatus = m_parallelNodeStatusHash.value(m_currentNodeStack);
					m_parallelNodeStatus->replace(parallel->childNodeIndex(currentNode), m_nodeStatus);
					m_parallelNodeStatusHash.remove(m_currentNodeStack, m_parallelNodeStatus);
				}
				
				delete m_currentNodeStack;
				m_currentNodeStack = NULL;
			}
			
			if(QString(currentNode->metaObject()->className()) == "btParallelNode")
			{				
				stopParallelExecution(currentNode);
			}
			
			if(m_currentNodeStack)
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
			break;
	}
}

void btCharacter::stopParallelExecution(btNode * currentNode)
{
	int counter = m_currentNodeStackQueue.count();
	
	while (counter > 0)
	{
		QStack<btNode*> * stack = m_currentNodeStackQueue.dequeue();
		if(stack->front() == currentNode)
		{
			m_parallelNodeStatusHash.remove(stack, m_parallelNodeStatusHash.value(stack));
			delete stack;
			
			m_visitedProbChildrenHash.remove(stack);
			
			m_nodesStatusQueue.dequeue();
			m_currentChildStackQueue.dequeue();
		}									 
		else
		{
			m_currentNodeStackQueue.enqueue(stack);
			m_nodesStatusQueue.enqueue(m_nodesStatusQueue.dequeue());
			m_currentChildStackQueue.enqueue(m_currentChildStackQueue.dequeue());
		}
		
		counter--;
	}
}

#include "btcharacter.moc"
