#ifndef GOUPNODE_H
#define GOUPNODE_H

#include <QObject>

#include "../gluon-bt-lib/btlib.h"


class goUpNode : public btNodeType
{
    Q_OBJECT
    
public:
    Q_INVOKABLE goUpNode();
    bool run(btCharacter *self);
};


#endif // GOUPNODE_H
