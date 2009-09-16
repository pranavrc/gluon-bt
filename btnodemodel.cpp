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

int btnodemodel::columnCount(const QModelIndex &parent) const
{
    return 2;
}

QVariant btnodemodel::data(const QModelIndex &index, int role) const
 {
     if (!index.isValid())
         return QVariant();

     if (index.row() >= nodeList.size())
         return QVariant();

     if (role == Qt::DisplayRole){
         if(index.column() == 0){
            return nodeList.at(index.row())->name();
        }else if(index.column() == 1){
            return nodeList.at(index.row())->description();
        }
     }else{
         return QVariant();
     }
 }

QVariant btnodemodel::headerData(int section, Qt::Orientation orientation,
                                      int role) const
 {
     if (role != Qt::DisplayRole)
         return QVariant();

     if (orientation == Qt::Horizontal){
         switch(section){
             case 0:
                return QString("Name");
             case 1:
                return QString("Discription");
             default:
                return QString("Column %1").arg(section);
         }
         //return QString("Column %1").arg(section);
     }else{
         return QString("Prop %1").arg(section);
     }
 }
