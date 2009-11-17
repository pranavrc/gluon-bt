#ifndef GORIGHTNODE_H
#define GORIGHTNODE_H

#include <QObject>

#include "../gluon-bt-lib/btlib.h"

class goRightNode : public btNodeType
{
    Q_OBJECT
    
public:
    Q_INVOKABLE goRightNode();
    bool run();
};


#endif // GORIGHTNODE_H
