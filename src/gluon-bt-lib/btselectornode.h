#ifndef BTSELECTORNODE_H
#define BTSELECTORNODE_H

#include <QObject>
#include "btnodetype.h"
#include "btfactory.h"

class btSelectorNode : public btNodeType{
        Q_OBJECT
    
    public:
        btSelectorNode() {}
        bool run();
};

REGISTER_NODETYPE(btSelectorNode)

#endif //BTSELECTORNODE_H
