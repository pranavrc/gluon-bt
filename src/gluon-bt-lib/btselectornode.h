#ifndef BTSELECTORNODE_H
#define BTSELECTORNODE_H

#include <QObject>

#include "btnodetype.h"
#include "btfactory.h"
#include "btcharacter.h"
#include "btlib_export.h"

class BT_LIB_EXPORT btSelectorNode : public btNodeType
{
    Q_OBJECT
    
public:
    Q_INVOKABLE btSelectorNode();
    bool run(btCharacter *self);
};

#endif //BTSELECTORNODE_H
