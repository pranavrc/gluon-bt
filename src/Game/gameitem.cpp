#include "gameitem.h"
#include <QDebug>
#include "game.h"
#include <QTimeLine>
#include <QGraphicsItemAnimation>
#include <QObject>

void GameItem::setupAnimation(){
     timer = new QTimeLine(20);
     timer->setFrameRange(0, 2);

     animation = new QGraphicsItemAnimation;
     animation->setTimeLine(timer);
     animation->setItem(this);
     timer->setCurveShape(QTimeLine::LinearCurve);
     QObject::connect(timer, SIGNAL(finished()),
                      this, SLOT(animationDone()));
}

void GameItem::setAnimationStep(QPoint from,QPoint to, Direction dir){
    this->dir = dir;
    animation->setPosAt(0, QPointF((from.x() * 20) + 10, (from.y() * 20.0) + 10));
    switch(dir){
        case Up:
            animation->setPosAt(1, QPointF((from.x() * 20) + 10, ((from.y() - 1) * 20.0) + 10));
            break;
        case Down:
            animation->setPosAt(1, QPointF((from.x() * 20) + 10, ((from.y() + 1) * 20.0) + 10));
            break;
        case Left:
            animation->setPosAt(1, QPointF(((from.x() - 1) * 20) + 10, (from.y() * 20.0) + 10));
            break;
        case Right:
            animation->setPosAt(1, QPointF(((from.x() + 1) * 20) + 10, (from.y() * 20.0) + 10));
            break;
    }

    game->board[square.x()][square.y()]->setVisible(false);
    timer->start();
}

void GameItem::animationDone()
{
    animation->clear();
    switch(dir){
        case Up:
            setSquare(square.x(),square.y() - 1);
            break;
        case Down:
            setSquare(square.x(),square.y() + 1);
            break;
        case Left:
            setSquare(square.x() - 1,square.y());
            break;
        case Right:
            setSquare(square.x() + 1,square.y());
            break;
    }
    if(move(dir)){
        setAnimationStep(square,QPoint(square.x(),square.y()),this->dir);
    }
}

GameItem::GameItem()
{

}

GameItem::GameItem(Game* game)
{
    myPolygon << QPointF(-10, 0) << QPointF(0, 10)
            << QPointF(10, 0) << QPointF(0, -10)
            << QPointF(-10, 0);
    this->setPolygon(myPolygon);
    setFlag(QGraphicsItem::ItemIsMovable, true);
    setFlag(QGraphicsItem::ItemIsSelectable, true);
    setSquare(0,0);
    this->game = game;
    setupAnimation();
}

GameItem::GameItem(int x,int y,Game* game){
    myPolygon << QPointF(-10, 0) << QPointF(0, 10)
                      << QPointF(10, 0) << QPointF(0, -10)
                      << QPointF(-10, 0);
    this->setPolygon(myPolygon);

    setSquare(x,y);
    this->game = game;
    setupAnimation();
}

void GameItem::setSquare(int x,int y){
    square.setX(x);
    square.setY(y);
    setPos((x * 20)+ 10,(y * 20) +10);
}

QVariant GameItem::itemChange(GraphicsItemChange change,
                     const QVariant &value)
{
   // qDebug() << "item changed";

    return value;
}

bool GameItem::move(Direction dir)
{
    bool value = true;
    switch(dir){
    case Up:
        value = square.y() > 0 && !(game->board[square.x()][square.y() - 1]->blocks());
        break;
    case Down:
        value = square.y() < 14 && !(game->board[square.x()][square.y() + 1]->blocks());
        break;
    case Left:
        value = square.x() > 0 && !game->board[square.x() - 1][square.y()]->blocks();
        break;
    case Right:
        value = square.x() < 14 && !game->board[square.x() + 1][square.y()]->blocks();
        break;
    default:
        return false;
    }
    return value;
}

bool GameItem::goUp()
{
    //qDebug("going up");
    if(move(Up)){
        setAnimationStep(square,QPoint(square.x(),square.y() + 1), Up);
        return true;
    }
    qDebug("action up failed");
    emit actionFailed();
    return false;
}

bool GameItem::goDown()
{
    //qDebug("going down");
    if(move(Down)){
        //qDebug("going down 2");

        setAnimationStep(square,QPoint(square.x(),square.y() + 1), Down);
        return true;
    }
    qDebug("action down failed");
    emit actionFailed();
    return false;
}

bool GameItem::goLeft()
{
    //qDebug("going left");
    if(move(Left)){
        setAnimationStep(square,QPoint(square.x(),square.y() + 1), Left);
        return true;
    }
    qDebug("action left failed");
    emit actionFailed();
    return false;
}

bool GameItem::goRight()
{
    //qDebug("going right");
    if(move(Right)){
        setAnimationStep(square,QPoint(square.x(),square.y() + 1), Right);
        return true;
    }
    qDebug("action right failed");
    emit actionFailed();
    return false;
}

bool GameItem::blocks()
{
    return blocking;
}

void GameItem::setBlocks(bool value)
{
    blocking = value;
}

//#include "gameitem.moc"
