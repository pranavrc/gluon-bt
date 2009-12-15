#ifndef MOVECLOSERLEFTRIGHTTOGOAL_H
#define MOVECLOSERLEFTRIGHTTOGOAL_H

#include <QObject>

#include "../gluon-bt-lib/btlib.h"


class moveCloserLeftRightToGoal : public btNodeType
{
    Q_OBJECT
    
public:
    Q_INVOKABLE moveCloserLeftRightToGoal();
    bool run(btCharacter *self);
};


#endif // MOVECLOSERLEFTRIGHTTOGOAL_H
