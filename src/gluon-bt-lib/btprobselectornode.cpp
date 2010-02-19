#include "btprobselectornode.h"

REGISTER_NODETYPE(btProbSelectorNode)

#include <QDebug>
#include <QDateTime>
#include <QVariant>

btProbSelectorNode::btProbSelectorNode()
{
    qsrand(QDateTime::currentDateTime().toTime_t());
	m_currentScale = 1.0f;
	m_currentStart = 0.0f;
}

btNode::status btProbSelectorNode::run(btCharacter *self)
{
	if(this->currentChildStatus() == Succeeded)
	{
		return Succeeded;
	}
	
	float randNum = ((float)qrand()/RAND_MAX) * m_currentScale;
	
	for(int i = 0; i < m_probStats.count(); i++)
	{
		StatNode * node = m_probStats[i];
		
		if(node->visited == false)
		{
			if(start < randNum && randNum <= (node->probability + start))
			{				
				if(parentNode()->child(inc)->runBehavior(self))
				{
					foreach(StatNode *node, m_probStats)
					{
						node->visited = false;
					}
					return Succeeded;
				}
				else
				{
					node->visited = true;
					scale -= node->probability;
				}
			}
			intStart += node->wp;
		}
	}
	
	/*float randNum;
	float intStart = 0.0;
	float scale = 1.0;
	int inc = 0;
	
	for(int i = 0; i < probStats.count(); i++)
	{
		//  qDebug() << qrand();
		randNum = ((float)qrand()/RAND_MAX) * scale;
		// qDebug() << "RandNum: " << randNum;
		foreach(StatNode *node, probStats)
		{
			if(node->visited == false)
			{
				if(intStart < randNum && randNum <= (node->wp + intStart)){
					//    qDebug() << intStart << " < " << randNum << " <= " << node->wp + intStart << " YES";
					if(stopFlag())
					{  // måske kan man gøre det til en del af runBehavior ?
						setStopFlag(false);
						return false;
					}
					if(parentNode()->child(inc)->runBehavior(self))
					{
						qDebug("behavior run succes");
						node->succes += 1;
						foreach(StatNode *node, probStats)
						{
							node->visited = false;
						}
						setStopFlag(false);
						return true;
					
					}
					else
					{
						qDebug("behavior run fail");
						node->fail += 1;
						node->visited = true;
						scale -= node->wp;
					}
				}
				intStart += node->wp;
			}
			inc += 1;
		}
		intStart = 0.0;
		inc = 0;
	}
	 //*/
	
    this->resetVisitedNodes();
	
	m_currentScale = 1.0f;
	m_currentStart = 0.0f;
	
    return Failed;
}

void btProbSelectorNode::appendingChild(int index)
{
    StatNode *newNode = new StatNode();
    //qDebug() << "prob stat insert at: " << index;
    m_probStats.insert(index,newNode);
}

void btProbSelectorNode::removingChild(int index)
{
    m_probStats.removeAt(index);
}

void btProbSelectorNode::childrenAdded()
{
    int count = m_probStats.count();
    int i = 0;
    if(count > 0)
	{
		
        if(property("weights").isValid())
		{
            QList<QVariant> probs = property("weights").toList();
			// qDebug() << "probs.count(): " << probs.count();
            foreach(StatNode *node, m_probStats)
			{
                node->probability = probs.at(i).toDouble();
                i++;
            }
        }
		else
		{
            foreach(StatNode *node, m_probStats)
			{
                node->probability = (1.0 / count);
            }
        }
    }
}

void btNode::resetVisitedNodes()
{
	foreach(StatNode *node, m_probStats)
	{
        node->visited = false;
    }
}

#include "btprobselectornode.moc"

