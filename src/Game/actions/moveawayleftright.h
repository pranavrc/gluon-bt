#ifndef MOVEAWAYLEFTRIGHT_H
#define MOVEAWAYLEFTRIGHT_H

#include <QObject>

#include "../gluon-bt-lib/btlib.h"


class moveAwayLeftRight : public btNodeType
{
    Q_OBJECT
    
public:
    Q_INVOKABLE moveAwayLeftRight();
    bool run(btCharacter *self);
};


#endif // MOVEAWAYLEFTRIGHT_H
