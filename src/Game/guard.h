#ifndef GUARD_H
#define GUARD_H

#include "agent.h"

class Guard : public Agent
{
public:
    Guard(Game* game,QPoint pos);
    void sayHello();
};

#endif // GUARD_H
