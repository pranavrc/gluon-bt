#include "btsequencenode.h"

#include "btnode.h"

btSequenceNode::btSequenceNode()
{
}

bool btSequenceNode::run()
{
    for(int i = 0; i < m_parent->childCount(); i++)
    {
        if(m_parent->child(i)->runBehavior())
        {
            return true;
        }
    }
    
    return false;
}

#include "btsequencenode.moc"
