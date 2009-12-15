#ifndef ISCLOSE_H
#define ISCLOSE_H

#include <QObject>

#include "../gluon-bt-lib/btlib.h"


class isClose : public btNodeType
{
    Q_OBJECT
    
public:
    Q_INVOKABLE isClose();
    bool run(btCharacter *self);
};


#endif // ISCLOSE_H
