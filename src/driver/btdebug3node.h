#ifndef BTDEBUG3_H
#define BTDEBUG3_H

#include <QObject>

#include "../gluon-bt-lib/btlib.h"

class btDebug3Node : public btNodeType
{
    Q_OBJECT
    
public:
    Q_INVOKABLE btDebug3Node();
    bool run();
};


#endif // BTDEBUG3_H
