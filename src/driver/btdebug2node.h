#ifndef BTDEBUG2_H
#define BTDEBUG2_H

#include <QObject>

#include "../gluon-bt-lib/btlib.h"

class btDebug2Node : public btNodeType
{
    Q_OBJECT
    
public:
    Q_INVOKABLE btDebug2Node();
    bool run();
};


#endif // BTDEBUG2_H
