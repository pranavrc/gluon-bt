#include "btselectornode.h"

#include "btnode.h"
#include "btcharacter.h"

btSelectorNode::btSelectorNode()
{
}

bool btSelectorNode::run(btCharacter *self)
{
    for(int i = 0; i < parentNode()->childCount(); i++)
    {
        if(stopFlag()){
            setStopFlag(false);
            return false;
        }
        if(parentNode()->child(i)->runBehavior(self))
        {
            qDebug() << "ran child: " << i;
            setStopFlag(false);
            return true;
        }
        qDebug() << "could not run child: " << i;
    }

    setStopFlag(false);
    return false;
}

#include "btselectornode.moc"
