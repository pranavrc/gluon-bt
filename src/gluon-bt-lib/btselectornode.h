#ifndef BTSELECTORNODE_H
#define BTSELECTORNODE_H

#include <QObject>
#include "btnodetype.h"

class btSelectorNode : public btNodeType{
        Q_OBJECT
    public:
        bool run();
};

#endif BTSELECTORNODE_H
