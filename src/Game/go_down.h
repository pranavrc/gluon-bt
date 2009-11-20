#ifndef GODOWNNODE_H
#define GODOWNNODE_H

#include <QObject>

#include "../gluon-bt-lib/btlib.h"

class goDownNode : public btNodeType
{
    Q_OBJECT
    
public:
    Q_INVOKABLE goDownNode();
    bool run(btCharacter *self);
};


#endif // GODOWNNODE_H
