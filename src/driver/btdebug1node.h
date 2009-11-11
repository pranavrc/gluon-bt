#ifndef BTDEBUG1_H
#define BTDEBUG1_H

#include <QObject>

#include "../gluon-bt-lib/btlib.h"

class btDebug1Node : public btNodeType
{
    Q_OBJECT
    
public:
    Q_INVOKABLE btDebug1Node();
    bool run();
};


#endif // BTDEBUG1_H
