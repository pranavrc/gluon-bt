#ifndef BTGOALNODE_H
#define BTGOALNODE_H

#include <QObject>

#include "../gluon-bt-lib/btlib.h"

class btGoalNode : public btNodeType
{
    Q_OBJECT
    
public:
    Q_INVOKABLE btGoalNode();
    bool run(btCharacter *self);
};


#endif // BTGOALNODE_H
