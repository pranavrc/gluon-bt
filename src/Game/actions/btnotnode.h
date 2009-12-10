#ifndef BTNOTNODE_H
#define BTNOTNODE_H

#include <QObject>

#include "../gluon-bt-lib/btlib.h"
#include "btlib_export.h"

class btNotNode : public btNodeType
{
    Q_OBJECT
    
public:
    Q_INVOKABLE btNotNode();
    bool run(btCharacter *self);
};

#endif
