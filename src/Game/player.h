#ifndef PLAYER_H
#define PLAYER_H

#include "agent.h"

class Player : public Agent
{
public:
    Player(Game* game,QPoint pos);
    void sayHello();
    void setSquare(int x,int y);
    void paint(QPainter *painter,
                           const QStyleOptionGraphicsItem *option,
                           QWidget *widget);

Q_SIGNALS:
    void pacmanWon();
    void pacmanLost();
    
    
private:
    int score;
};

#endif // PLAYER_H
