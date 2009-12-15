#ifndef MOVECLOSERUPDOWNTOGOAL_H
#define MOVECLOSERUPDOWNTOGOAL_H

#include <QObject>

#include "../gluon-bt-lib/btlib.h"


class moveCloserUpDownToGoal : public btNodeType
{
    Q_OBJECT
    
public:
    Q_INVOKABLE moveCloserUpDownToGoal();
    bool run(btCharacter *self);
};


#endif // MOVECLOSERUPDOWNTOGOAL_H
