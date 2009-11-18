#ifndef BTDEBUG_H
#define BTDEBUG_H

#include <QObject>

#include "../gluon-bt-lib/btlib.h"

class btDebugNode : public btNodeType
{
    Q_OBJECT
    
public:
    Q_INVOKABLE btDebugNode();
    bool run(btCharacter *self);
};


#endif // BTDEBUG_H
