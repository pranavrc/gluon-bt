#ifndef GAMEITEM_H
#define GAMEITEM_H

#include <QGraphicsPolygonItem>

class GameItem : public QGraphicsPolygonItem
{
public:
    GameItem();
private:
    QPolygonF myPolygon;
protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant &value);
};

#endif // GAMEITEM_H
