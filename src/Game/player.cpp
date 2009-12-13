#include "player.h"
#include "game.h"
#include "agent.h"

Player::Player(Game* game,QPoint pos)
        : Agent(game,pos)
{
    score = 0;
    setZValue(13);
    collided = false;
}

void Player::sayHello()
{
    Agent::sayHello();
    game->board[square.x()][square.y()]->setVisible(false);
}

void Player::setSquare(int x,int y){
    /*if(this->game->board[x][y]->occupant != NULL || this->game->board[square.x()][square.y()]->occupant != this ){
        qDebug("You Lost");
    }*/

    if(collided == true){
        qDebug("You Lost");
        emit pacmanLost();
    }
    if(this->game->board[x][y]->goal()){
        score++;
        if(score >= 5){
            qDebug("You Won");
            this->setBrush(QBrush(QColor(Qt::gray)));
            emit pacmanWon();
        }
    }

    Agent::setSquare(x,y);
}

 void Player::paint(QPainter *painter,
                           const QStyleOptionGraphicsItem *option,
                           QWidget *widget)
 {
     QGraphicsPolygonItem::paint(painter,option,widget);

     //qDebug() << "collided: " << collided;
     //qDebug() << "returnvalue: " << returnValue;

     if(collision() == true){
        qDebug() << "player collided";
        collided = true;
    }

 }
