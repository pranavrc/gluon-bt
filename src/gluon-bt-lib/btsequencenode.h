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
    btSequenceNode();
    bool run();
};

#endif
