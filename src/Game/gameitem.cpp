#include "gameitem.h"
#include <QDebug>

GameItem::GameItem()
{
    myPolygon << QPointF(-10, 0) << QPointF(0, 10)
                      << QPointF(10, 0) << QPointF(0, -10)
                      << QPointF(-10, 0);
    this->setPolygon(myPolygon);
     //   setFlag(QGraphicsItem::ItemIsMovable, true);
   // setFlag(QGraphicsItem::ItemIsSelectable, true);
}

QVariant GameItem::itemChange(GraphicsItemChange change,
                     const QVariant &value)
{
    qDebug() << "item changed";

    return value;
}
