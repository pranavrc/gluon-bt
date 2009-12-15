#ifndef MOVECLOSERLEFTRIGHTPINKY_H
#define MOVECLOSERLEFTRIGHTPINKY_H

#include <QObject>

#include "../gluon-bt-lib/btlib.h"
#include "gameitem.h"

static QPoint pinkySquare(QPoint square,GameItem::Direction dir)
{
    int d = 7;
    QPoint value(square.x(),square.y());
    if(dir == GameItem::Up){
        value.ry() -= d;
        if(value.y() < 0)
            value.ry() = 0;
    }
    if(dir == GameItem::Down){
        value.ry() += d;
        if(value.y() > 14)
            value.ry() = 14;
    }
    if(dir == GameItem::Left){
        value.rx() -= d;
        if(value.x() < 0)
            value.rx() = 0;
    }
    if(dir == GameItem::Right){
        value.rx() += d;
        if(value.x() > 14)
            value.rx() = 14;
    }
    return value;

}


class moveCloserLeftRightPinky : public btNodeType
{
    Q_OBJECT
    
public:
    Q_INVOKABLE moveCloserLeftRightPinky();
    bool run(btCharacter *self);
};


#endif // MOVECLOSERLEFTRIGHT_H
