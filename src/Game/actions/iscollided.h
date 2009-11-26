#ifndef ISCOLLIDED_H
#define ISCOLLIDED_H

#include <QObject>

#include "../gluon-bt-lib/btlib.h"


class isCollided : public btNodeType
{
    Q_OBJECT
    
public:
    Q_INVOKABLE isCollided();
    bool run(btCharacter *self);
};


#endif // ISCOLLIDED_H
