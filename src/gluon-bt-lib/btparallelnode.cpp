#include "btparallelnode.h"

#include <QtCore/QDebug>
#include <QtCore/QVariant>

REGISTER_NODETYPE(btParallelNode)

btParallelNode::btParallelNode()
{
	this->setCurrentChildStatus(Running);
}

btNode::status btParallelNode::run(btCharacter *self)
{	
	if(this->currentChildStatus() == None)
	{
		return Running;
	}
		
	return this->currentChildStatus();
}

void btParallelNode::appendingChild(int index)
{
	QStack<btNode*> nodes = QStack<btNode*>();
	nodes.push(this);
	nodes.push(this->child(index));
	//m_childNodes.enqueue(nodes);
	m_childNodes.append(nodes);
	
	QStack<int> nodesIndex = QStack<int>();
	nodesIndex.push(0);
	//m_childNodesIndex.enqueue(nodesIndex);
	m_childNodesIndex.append(nodesIndex);
	
	m_runningNodesStatus.insert(index, btNode::None);
	
	/*QStack<btNode*> parent = QStack<btNode*>();
	parent.push(this);
	m_parents.insert(index, parent);*/
	
	m_nodesIndex[this->child(index)] = index;
}

void btParallelNode::removingChild(int index)
{
	m_childNodes.removeAt(index+1);
	m_childNodesIndex.removeAt(index);
	m_runningNodesStatus.removeAt(index);
	//m_parents.removeAt(index);
	m_nodesIndex.remove(this->child(index));
}

void btParallelNode::childrenAdded()
{	
	int count = m_childNodes.count();
    if(count > 0)
	{
		
        if(this->property("conditions").isValid())
		{
            QList<QVariant> conditions = property("conditions").toList();
			
			for	(int i = 0; i < count; i++)
			{
				if(conditions[i].toBool() == true)
				{
					m_conditionStatus.append(btNode::Succeeded);
				}
				else 
				{
					m_conditionStatus.append(btNode::Failed);
				}

			}
        }
		else
		{
            for (int i = 0; i < count; i++)
			{
				m_conditionStatus.append(btNode::Succeeded);
            }
        }
    }
}

//QQueue<QStack<btNode*> > btParallelNode::parallelChildren()
QList<QStack<btNode*> > btParallelNode::parallelChildren()
{
	return m_childNodes;
}

//QQueue<QStack<int> > btParallelNode::parallelChildrenIndex()
QList<QStack<int> > btParallelNode::parallelChildrenIndex()
{
	return m_childNodesIndex;
}

btNode::status btParallelNode::conditionsFulfilled()
{
	for (int i = 0; i < this->childCount(); i++)
	{
		if(m_runningNodesStatus[i] == btNode::None)
			return Running;
		
		if(m_runningNodesStatus[i] != m_conditionStatus[i])
			return Failed;
	}
	
	this->resetRunningNodesStatus();
	return Succeeded;
}

void btParallelNode::resetRunningNodesStatus()
{
	for (int i = 0; i < m_runningNodesStatus.count(); i++)
	{
		m_runningNodesStatus[i] = btNode::None;
	}
}

QList<btNode::status> btParallelNode::runningNodesStatus()
{
	return m_runningNodesStatus;
}

void btParallelNode::setRunningNodesStatus(QList<btNode::status> nodeStatus)
{
	m_runningNodesStatus = nodeStatus;
}

QList<QStack<btNode*> > btParallelNode::runningNodesParents()
{
	return m_parents;
}

int btParallelNode::childNodeIndex(btNode* childNode)
{	
	return m_nodesIndex[childNode];
}

#include "btparallelnode.moc"

