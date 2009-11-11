#ifndef BTBLOCKERNODE_H
#define BTBLOCKERNODE_H

#include <QObject>

#include "../gluon-bt-lib/btlib.h"

class btBlockerNode : public btNodeType
{
    Q_OBJECT
    
public:
    Q_INVOKABLE btBlockerNode();
    bool run();
};


#endif // BTBLOCKERNODE_H
