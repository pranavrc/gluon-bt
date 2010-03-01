#include "btcharacter.h"

#include <QtCore/QDebug>

btCharacter::btCharacter()
{
	m_nodesStatusQueue.enqueue(btNode::None);
}

btCharacter::~btCharacter()
{
	for (int i = 0; i < m_currentNodeStackQueue.count(); i++)
	{
		delete m_currentNodeStackQueue.at(i).first;
	}
	m_currentNodeStackQueue.clear();
	
	qDeleteAll(m_visitedProbChildrenHash.keys());
	m_visitedProbChildrenHash.clear();
	
	qDeleteAll(m_parallelNodeStatusHash.values());
	qDeleteAll(m_parallelNodeStatusHash.keys());
			   
	m_parallelNodeStatusHash.clear();
			   
}

void btCharacter::setBehaviorTree(btNode* behaviorTree)
{
	m_behaviortree = behaviorTree;
	
	QStack<btNode*>* currentNodeStack = new QStack<btNode*>();
	currentNodeStack->push(m_behaviortree);
	
	QStack<int> currentChildStack = QStack<int>();
	currentChildStack.push(0);
	
	m_currentChildStackQueue.enqueue(currentChildStack);
	
	QPair<QStack<btNode*>*, QStack<btNode*>*> pair;
	pair.first = currentNodeStack;
	pair.second = NULL;
	m_currentNodeStackQueue.enqueue(pair);
}

void btCharacter::think()
{
	//local variables used in think
	btProbSelectorNode * probSelector = NULL;
	btParallelNode * parallel = NULL;
	btNode* currentParent = NULL;
	QStack<QList<ProbNode*> > visitedProbChildrenStack;
	QStack<btNode*>* currentNodeStack = NULL;
	QStack<int> currentChildStack;
	btNode::status nodeStatus;
	int currentChildIndex = 0;
	
	QPair<QStack<btNode*>*, QStack<btNode*>*> currentChildParentStackPair;
	
	//retrieve a execution stack
	currentChildParentStackPair = m_currentNodeStackQueue.dequeue();
	currentNodeStack = currentChildParentStackPair.first;
	currentChildStack = m_currentChildStackQueue.dequeue();
	nodeStatus = m_nodesStatusQueue.dequeue();
	
	//retrieve the executing node
	btNode* currentNode = currentNodeStack->top();
	
	//check if it s possible to set parent, and set it if possible
	if(currentNodeStack->count() > 1)
	{
		currentParent = currentNodeStack->at(currentNodeStack->count() - 2);
	}
	
	//check if it s possible to set current child, and set it if possible
	if(currentChildStack.count() > 0)
	{
		currentChildIndex = currentChildStack.pop();
	}
	
	if (QString(currentNode->metaObject()->className()) == "btProbSelectorNode")
	{
		//if the current node is a probselector, cast it
		probSelector = qobject_cast<btProbSelectorNode*>(currentNode);
		
		//and set the probnodes if we have run it before
		if(m_visitedProbChildrenHash.contains(currentNodeStack))
		{
			probSelector->setVisitedProbNodes(m_visitedProbChildrenHash[currentNodeStack].pop());
		}
	}
	else if (QString(currentNode->metaObject()->className()) == "btParallelNode")
	{
		//if the current node is a parallel, cast it
		parallel = qobject_cast<btParallelNode*>(currentNode);
		
		//if it is the first time, create execution stacks, child stacks etc. for each child and add them to the queue
		if(nodeStatus == btNode::None)
		{			
			QList<btNode::status>* childStatus = new QList<btNode::status>();
			
			for(int i = 0; i < parallel->childCount(); i++)
			{
				QStack<btNode*>* newStack = new QStack<btNode*>();
				newStack->push(parallel);
				newStack->push(parallel->child(i));
				//m_currentNodeStackQueue.enqueue(newStack);
				QPair<QStack<btNode*>*, QStack<btNode*>*> pair;
				pair.first = newStack;
				pair.second = currentNodeStack;
				m_currentNodeStackQueue.enqueue(pair);
				
				childStatus->append(btNode::None);
				m_nodesStatusQueue.enqueue(btNode::None);
				
				m_parallelNodeStatusHash.insert(newStack, childStatus);
				
				QStack<int> childStack = QStack<int>();
				childStack.push(0);
				m_currentChildStackQueue.append(childStack);
			}
				
			m_parallelNodeStatusHash.insert(currentNodeStack, childStatus);
			nodeStatus = btNode::Running;
		}
		
		//check if termination conditions is fulfilled, return btNode::Running if not
		parallel->setRunningNodesStatus(m_parallelNodeStatusHash.value(currentNodeStack));
		nodeStatus = parallel->conditionsFulfilled();
	}	
	
	//restore the execution state of the current executing node
	currentNode->setCurrentChildIndex(currentChildIndex);
	currentNode->setCurrentChildStatus(nodeStatus);
	currentNode->setParentNode(currentParent);
	
	qDebug() << currentNode->name();
	//run the node
	nodeStatus = currentNode->run(this);
	
	//handle the status messsage
	switch (nodeStatus)
	{
		case btNode::RunningChild:
			//when running child, push the child and child index onto the stacks
			currentNodeStack->push(currentNode->currentChild());
			currentChildStack.push(currentNode->currentChildIndex());
			
			//enqueue the stacks and status
			m_currentNodeStackQueue.enqueue(currentChildParentStackPair);
			m_currentChildStackQueue.enqueue(currentChildStack);
			
			m_nodesStatusQueue.enqueue(btNode::None);
			
			//if current node is a probselector, then save the probnodes
			if(probSelector)
			{
				m_visitedProbChildrenHash[currentNodeStack].push(probSelector->visitedProbNodes());
			}
			
			break;
		case btNode::Failed:
		case btNode::Succeeded:
			//when the node fails or succeeds
			if(currentNodeStack->count() > 1)
			{	
				//if there is more than one node in the stack, pop it
				currentNodeStack->pop();
				if(currentChildStack.count() > 0)
				{
					currentChildStack.pop();
				}
			}
			else
			{	
				//else check > 0 then set it as the top, else push a 0 on it
				if(currentChildStack.count() > 0)
				{
					currentChildIndex = currentChildStack.top();
				}
				else
				{
					currentChildStack.push(0);
				}
				
				//if the node is the root, reset status
				if(currentNode == m_behaviortree)
					nodeStatus = btNode::None;
			}	
			
			if(QString(currentNode->metaObject()->className()) == "btProbSelectorNode")
			{				
				//if probselector then remove the probnodes for this stack
				m_visitedProbChildrenHash.remove(currentNodeStack);
			}
			
			//bool indicating if deletion of stack is necessary
			if(currentParent != NULL && QString(currentParent->metaObject()->className()) == "btParallelNode")
			{
				//if the parent is a parallel, set the status for that parallel.
				parallel = qobject_cast<btParallelNode*>(currentParent);
				QList<btNode::status>* m_parallelNodeStatus = m_parallelNodeStatusHash.value(currentNodeStack);
				m_parallelNodeStatus->replace(parallel->childNodeIndex(currentNode), nodeStatus);
				m_parallelNodeStatusHash.remove(currentNodeStack, m_parallelNodeStatus);
				
				if(m_parallelNodeStatusHash.count(currentNodeStack) == 0)
				{
					//remove the stack if there is no other node status in the hash
					delete currentNodeStack;
					currentNodeStack = NULL;					
				}
			}
			
			if(QString(currentNode->metaObject()->className()) == "btParallelNode")
			{				
				//if parallel stop the children and remove the node status list from the hash
				stopParallelExecution(currentNode, currentChildParentStackPair.second);
				
				if(currentNodeStack)
				{
					QList<btNode::status>* status = m_parallelNodeStatusHash.value(currentNodeStack);
					m_parallelNodeStatusHash.remove(currentNodeStack, m_parallelNodeStatusHash.value(currentNodeStack));
					delete status;
				}
			}
			
			if(currentNodeStack)
			{				
				//if node stack is not deleted, enqueue it again
				m_currentNodeStackQueue.enqueue(currentChildParentStackPair);
				m_currentChildStackQueue.enqueue(currentChildStack);
				m_nodesStatusQueue.enqueue(nodeStatus);
			}			
			break;
		case btNode::Running:
			//enqueue stack and stuff
			currentChildIndex = currentNode->currentChildIndex();			
			m_currentNodeStackQueue.enqueue(currentChildParentStackPair);
			currentChildStack.push(currentChildIndex);
			m_currentChildStackQueue.enqueue(currentChildStack);
			m_nodesStatusQueue.enqueue(nodeStatus);
			break;
	}
}

void btCharacter::stopParallelExecution(btNode * currentNode, QStack<btNode*>* parentStack)
{
	int counter = m_currentNodeStackQueue.count();
	
	while (counter > 0)
	{
		QPair<QStack<btNode*>*, QStack<btNode*>*> pair =  m_currentNodeStackQueue.dequeue();
		if(pair.first->front() == currentNode && pair.second == parentStack)
		{
			QList<btNode::status>* status = m_parallelNodeStatusHash.value(pair.first);
			m_parallelNodeStatusHash.remove(pair.first, m_parallelNodeStatusHash.value(pair.first));
			delete pair.first;
			delete status;
			
			m_visitedProbChildrenHash.remove(pair.first);
			
			m_nodesStatusQueue.dequeue();
			m_currentChildStackQueue.dequeue();
		}									 
		else
		{
			m_currentNodeStackQueue.enqueue(pair);
			m_nodesStatusQueue.enqueue(m_nodesStatusQueue.dequeue());
			m_currentChildStackQueue.enqueue(m_currentChildStackQueue.dequeue());
		}
		
		counter--;
	}
}

#include "btcharacter.moc"
