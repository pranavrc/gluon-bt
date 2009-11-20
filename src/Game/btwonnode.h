#ifndef BTWONNODE_H
#define BTWONNODE_H

#include <QObject>

#include "../gluon-bt-lib/btlib.h"

class btWonNode : public btNodeType
{
    Q_OBJECT
    
public:
    Q_INVOKABLE btWonNode();
    bool run(btCharacter *self);
};


#endif // BTWONNODE_H
