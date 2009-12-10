#include "player.h"
#include "game.h"
#include "agent.h"

Player::Player(Game* game,QPoint pos)
        : Agent(game,pos)
{
    score = 0;
    setZValue(13);
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
    }
    if(this->game->board[x][y]->goal()){
        score++;
        if(score >= 5){
            qDebug("You Won");
            this->setBrush(QBrush(QColor(Qt::gray)));
        }
    }

    Agent::setSquare(x,y);
}

 void Player::paint(QPainter *painter,
                           const QStyleOptionGraphicsItem *option,
                           QWidget *widget)
 {
     QGraphicsPolygonItem::paint(painter,option,widget);
     if(collision() == true){
        qDebug() << "player collided";
        collided = true;
    }

 }
