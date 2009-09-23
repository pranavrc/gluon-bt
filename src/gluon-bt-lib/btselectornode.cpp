#include "btselectornode.h"

#include "btnode.h"

btSelectorNode::btSelectorNode()
{
    qsrand(QDateTime::currentDateTime().toTime_t());
}

bool btSelectorNode::run()
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

#include "btselectornode.moc"