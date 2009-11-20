#include "agent.h"
#include <QDebug>
#include <QDateTime>
#include "btlib.h"

Agent::Agent()
{

}

Agent::Agent(Game* game)
        : GameItem(game)
{
    this->game->addItem(this);
    QObject::connect(timer, SIGNAL(finished()),
                     this, SLOT(sayHello()));
    QObject::connect(this, SIGNAL(actionFailed()),
                     this, SLOT(unlock()));

    this->setBrush(QBrush(QColor(Qt::green)));
}

Agent::Agent(Game* game,QPoint pos)
        :GameItem(game)
{
    this->game->addItem(this);
    QObject::connect(timer, SIGNAL(finished()),
                     this, SLOT(sayHello()));
        QObject::connect(this, SIGNAL(actionFailed()),
                     this, SLOT(unlock()));
    this->setBrush(QBrush(QColor(Qt::green)));
    this->setSquare(pos.x(),pos.y());
    this->returnValue = true;
    /*if(move(Right)){
        this->goRight();
    }else{
        this->goLeft();
    }*/
}

void Agent::unlock()
{
    returnValue = false;
    qDebug() << "unlock";
    mutex->unlock();
    waitCond->wakeAll();
}

void Agent::sayHello()
{
    int count = 0;
    QList<int> possibleMove;
    if(dir == Up || dir == Down){
        if(move(Right)){
            possibleMove.append(Right);
            count++;
        }
        if(move(Left)){
            possibleMove.append(Left);
            count++;
        }
    }else if(dir == Left || dir == Right){
        if(move(Up)){
            possibleMove.append(Up);
            count++;
        }
        if(move(Down)){
            possibleMove.append(Down);
            count++;
        }
    }

    /*if(move(dir)){
        possibleMove.append(dir);
        count++;
    }*/


    /*qrand();

    int r = 0;
    if(count == 3){
        r = qrand() % 3;
    }
    else if(count == 2){
        r = qrand() % 2;
    }

    if(count == 0){
        return;
    }*/

    /*//qDebug() << possibleMove;

    //qDebug() << "random: " << r;

    int c = possibleMove.at(r);
    //qDebug() << "choose: " << c;
    //int c = 0;

    switch(c){
        case Up:
            goUp();
            break;
        case Down:
            goDown();
            break;
        case Left:
            goLeft();
            break;
        case Right:
            goRight();
            break;
    }*/
    qDebug() << "callback";
    if(count >= 1){
        returnValue = true;
        mutex->unlock();
        waitCond->wakeAll();
    }
}

GameItem::Direction Agent::choose()
{
    return Down;
}

void Agent::setSquare(int x,int y){
    square.setX(x);
    square.setY(y);
    setPos((x * 20)+ 10,(y * 20) +10);
    this->game->board[square.x()][square.y()]->occupant = this;
    //this->goDown();
}
