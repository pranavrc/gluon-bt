#include "btnodemodel.h"
#include "btnodetypesmodel.h"

btnodemodel::btnodemodel(QList<btNodeType *> nodetypes,QObject *parent)
        :QAbstractTableModel(parent)
{
    nodeList = nodetypes;
}

int btnodemodel::rowCount(const QModelIndex &parent) const
{
    return nodeList.count();
}

QVariant btnodemodel::data(const QModelIndex &index, int role) const
 {
     if (!index.isValid())
         return QVariant();

     if (index.row() >= nodeList.size())
         return QVariant();

     if (role == Qt::DisplayRole)
         return nodeList.at(index.row())->name();
     else
         return QVariant();
 }

QVariant btnodemodel::headerData(int section, Qt::Orientation orientation,
                                      int role) const
 {
     if (role != Qt::DisplayRole)
         return QVariant();

     if (orientation == Qt::Horizontal)
         return QString("Column %1").arg(section);
     else
         return QString("Row %1").arg(section);
 }
