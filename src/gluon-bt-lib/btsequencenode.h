#ifndef BTSEQUENCENODE_H
#define BTSEQUENCENODE_H

#include <QObject>

#include "btnodetype.h"
#include "btfactory.h"

#include "btlib_export.h"

class BT_LIB_EXPORT btSequenceNode : public btNodeType
{
    Q_OBJECT
    
public:
    Q_INVOKABLE btSequenceNode();
    bool run();
};

#endif
