#ifndef MOVECLOSERUPDOWNPINKY_H
#define MOVECLOSERUPDOWNPINKY_H

#include <QObject>

#include "../gluon-bt-lib/btlib.h"


class moveCloserUpDownPinky : public btNodeType
{
    Q_OBJECT
    
public:
    Q_INVOKABLE moveCloserUpDownPinky();
    bool run(btCharacter *self);
};


#endif // MOVECLOSERUPDOWN_H
