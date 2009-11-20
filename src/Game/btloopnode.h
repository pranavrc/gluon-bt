#ifndef BTLOOPNODE_H
#define BTLOOPNODE_H

#include <QObject>

#include "../gluon-bt-lib/btlib.h"
#include "btlib_export.h"

class btLoopNode : public btNodeType
{
    Q_OBJECT
    
public:
    Q_INVOKABLE btLoopNode();
    bool run(btCharacter *self);
};

#endif
