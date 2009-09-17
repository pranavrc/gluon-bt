#ifndef BTNODEMODEL_H
#define BTNODEMODEL_H

#include <QAbstractTableModel>
#include <QVariant>
#include <QModelIndex>
#include "btnodetype.h"

class btnodemodel : public QAbstractTableModel
{
public:
    btnodemodel(btNodeType * nodetypes,QObject *parent = 0);
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section,Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const;
private:
    QList<btNodeType *>     nodeList;
    btNodeType *     node;
};

#endif // BTNODEMODEL_H
