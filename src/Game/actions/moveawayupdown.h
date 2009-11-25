#ifndef MOVEAWAYUPDOWN_H
#define MOVEAWAYUPDOWN_H

#include <QObject>

#include "../gluon-bt-lib/btlib.h"


class moveAwayUpDown : public btNodeType
{
    Q_OBJECT
    
public:
    Q_INVOKABLE moveAwayUpDown();
    bool run(btCharacter *self);
};


#endif // MOVEAWAYUPDOWN_H
