#ifndef STOPMOVE_H
#define STOPMOVE_H

#include <QObject>

#include "../gluon-bt-lib/btlib.h"


class stopMove : public btNodeType
{
    Q_OBJECT
    
public:
    Q_INVOKABLE stopMove();
    bool run(btCharacter *self);
};


#endif // STOPMOVE_H
