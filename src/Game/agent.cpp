#include "agent.h"
#include "game.h"
#include <QDebug>
#include <QDateTime>
#include "btlib.h"

Agent::Agent()
{
    collided = false;
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
    collided = false;
}

Agent::Agent(Game* game,QPoint pos)
        :GameItem(game)
{
    dir = Up;
    this->game->addItem(this);
    QObject::connect(timer, SIGNAL(finished()),
                     this, SLOT(sayHello()));
        QObject::connect(this, SIGNAL(actionFailed()),
                     this, SLOT(unlock()));
    this->setBrush(QBrush(QColor(Qt::green)));
    this->setSquare(pos.x(),pos.y());
    this->returnValue = true;
    collided = false;
}

 void Agent::paint(QPainter *painter,
                           const QStyleOptionGraphicsItem *option,
                           QWidget *widget)
 {
     QGraphicsPolygonItem::paint(painter,option,widget);
     if(collision() == true){
        //qDebug() << "coliided and repainted";
        collided = true;
    }else{
        collided = false;
    }
 }

void Agent::unlock()
{
    returnValue = false;
 //   qDebug() << "unlock";
    //mutex->unlock();
    waitCond->wakeAll();
  //  qDebug() << "unlock2";
    //eventMutex->unlock();
    eventCond->wakeAll();
  //  qDebug() << "done unlucking and waking"; 
}

void Agent::sayHello()
{
    int count = 0;
    //QList<int> possibleMove;
    if(dir == Up || dir == Down){
        if(move(Right)){
           // possibleMove.append(Right);
            count++;
        }
        if(move(Left)){
          //  possibleMove.append(Left);
            count++;
        }
    }else if(dir == Left || dir == Right){
        if(move(Up)){
          //  possibleMove.append(Up);
            count++;
        }
        if(move(Down)){
           // possibleMove.append(Down);
            count++;
        }
    }

    //qDebug() << "callback";
    if(count >= 1){
        returnValue = true;
        //mutex->unlock();
        waitCond->wakeAll();
    }
    //eventMutex->unlock();
    //collided = false;   // don't know if this is the right place
    eventCond->wakeAll();
}


void Agent::setSquare(int x,int y){
    squareLock.lock();
    
    if(x < 0)
        x = 0;
    
    if(y < 0)
        y = 0;
    
    if(y > 14)
        y = 14;
    
    if(x > 14)
        x = 14;

    emit enteredNewCell(x,y);

    this->game->board[square.x()][square.y()]->occupant = NULL;
    square.setX(x);
    square.setY(y);
    setPos((x * 20)+ 10,(y * 20) +10);
    this->game->board[square.x()][square.y()]->occupant = this;
    squareLock.unlock();

}

bool Agent::forward()
{
    if(dir == Up){ return goUp(); }
    if(dir == Down){ return goDown(); }
    if(dir == Left){ return goLeft(); }
    if(dir == Right){ return goRight(); }
}

bool Agent::back()
{
    if(dir == Up){ return goDown(); }
    if(dir == Down){ return goUp(); }
    if(dir == Left){ return goRight(); }
    if(dir == Right){ return goLeft(); }
}

bool Agent::relativeLeft()
{
    if(dir == Up){ return goLeft(); }
    if(dir == Down){ return goRight(); }
    if(dir == Left){ return goDown(); }
    if(dir == Right){ return goUp(); }
}

bool Agent::relativeRight()
{
    if(dir == Up){ return goRight(); }
    if(dir == Down){ return goLeft(); }
    if(dir == Left){ return goUp(); }
    if(dir == Right){ return goDown(); }
}

bool Agent::stopMove()
{
    animation->clear();
}

bool Agent::collision(){
    if(!scene()->collidingItems(this).isEmpty()){
        foreach(QGraphicsItem* item,scene()->collidingItems(this)){
            if(item == static_cast<QGraphicsItem*>(this)){
                continue;
            }
            if(item->zValue() >= 10){
                //returnValue = true;
                //qDebug() << "collision";
                return true;
            }
        }
        //qDebug() << "hey";
        //return false;
        //qDebug() << "no collision";
        //returnValue = false;
    }
    return false;
}

QList<Agent*> Agent::getObjectives()
{
    return objectives;
}

void Agent::addObjective(Agent* o)
{
    objectives.append(o);
}

QList<GameItem*> Agent::getGoals()
{
    return goals;
}

void Agent::addGoal(GameItem* o)
{
    goals.append(o);
}


#include "agent.moc"
