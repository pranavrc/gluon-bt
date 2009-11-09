#ifndef BTSEQUENCENODE_H
#define BTSEQUENCENODE_H

#include <QObject>

#include "btnodetype.h"
#include "btfactory.h"

class btSequenceNode : public btNodeType
{
    Q_OBJECT
    
public:
    btSequenceNode();
    bool run();
};

#endif
