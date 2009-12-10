#ifndef PLAYER_H
#define PLAYER_H

#include "agent.h"

class Player : public Agent
{
public:
    Player(Game* game,QPoint pos);
    void sayHello();
    void setSquare(int x,int y);
    void collided();

private:
    int score;
};

#endif // PLAYER_H
