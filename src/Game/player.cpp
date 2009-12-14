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
    QColor color = game->board[square.x()][square.y()]->brush().color().darker(105);
    game->board[square.x()][square.y()]->setBrush(QBrush(color));
}

void Player::setSquare(int x,int y){
    /*if(this->game->board[x][y]->occupant != NULL || this->game->board[square.x()][square.y()]->occupant != this ){
        qDebug("You Lost");
    }*/
    
    if(x < 0)
        x = 0;
    
    if(y < 0)
        y = 0;
    
    if(y > 14)
        y = 14;
    
    if(x > 14)
        x = 14;
    
    emit enteredNewCell(x,y);
    if(collided == true){
       // qDebug("You Lost");
        emit pacmanLost();
    }
    if(this->game->board[x][y]->goal()){
        score++;
        if(score >= 5){
          //  qDebug("You Won");
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
        //qDebug() << "player collided";
        collided = true;
    }

 }

#include "player.moc"
