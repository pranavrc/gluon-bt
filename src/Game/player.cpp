#include "player.h"
#include "game.h"
#include "agent.h"

Player::Player(Game* game,QPoint pos)
        : Agent(game,pos)
{
    score = 0;
    setZValue(13);
    collided = false;
    counter = 0;
}

void Player::sayHello()
{
    Agent::sayHello();
    //QColor color = game->board[square.x()][square.y()]->brush().color().darker(102);
    //game->board[square.x()][square.y()]->setBrush(QBrush(color));
    if(game->board[square.x()][square.y()]->goal()){
        game->board[square.x()][square.y()]->setVisible(false);
        game->board[square.x()][square.y()]->setGoal(false);
    }
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
    qDebug() << "entered a cell";
    //emit enteredNewCell(x,y);
    if(collided == true){
       // qDebug("You Lost");
        counter++;
        if(counter == 1)
            emit pacmanLost();
    }
    if(this->game->board[x][y]->goal()){
        score++;
        this->game->board[x][y]->setVisible(false);
        if(score >= 7){
          //  qDebug("You Won");
           // this->setBrush(QBrush(QColor(Qt::gray)));
            score = 0;
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
