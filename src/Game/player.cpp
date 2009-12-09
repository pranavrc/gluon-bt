#include "player.h"
#include "game.h"
#include "agent.h"

Player::Player(Game* game,QPoint pos)
        : Agent(game,pos)
{
    score = 0;
}

void Player::sayHello()
{
    Agent::sayHello();
    game->board[square.x()][square.y()]->setVisible(false);
}

void Player::setSquare(int x,int y){
    if(this->game->board[x][y]->occupant != NULL || this->game->board[square.x()][square.y()]->occupant != this ){
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

void Player::collided(){
    qDebug("You Lost");
}
