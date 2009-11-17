#ifndef GOLEFTNODE_H
#define GOLEFTNODE_H

#include <QObject>

#include "../gluon-bt-lib/btlib.h"

class goLeftNode : public btNodeType
{
    Q_OBJECT
    
public:
    Q_INVOKABLE goLeftNode();
    bool run();
};


#endif // GOLEFTNODE_H
