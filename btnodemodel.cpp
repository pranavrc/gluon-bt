#include "btnodemodel.h"
#include "btnodetypesmodel.h"

btnodemodel::btnodemodel(btNodeType * nodetype,QObject *parent)
        :QAbstractTableModel(parent)
{
    node = nodetype;
}

int btnodemodel::rowCount(const QModelIndex &parent) const
{
    return node->dynamicPropertyNames().count();
}

int btnodemodel::columnCount(const QModelIndex &parent) const
{
    return 3;
}

QVariant btnodemodel::data(const QModelIndex &index, int role) const
 {
     if (!index.isValid())
         return QVariant();

     if (index.row() >= node->dynamicPropertyNames().count())
         return QVariant();

     if (role == Qt::DisplayRole){
         switch(index.column()){
             case 0:
                return node->dynamicPropertyNames().at(index.row());
             case 1:
                return node->property(node->dynamicPropertyNames().at(index.row()));
             case 2:
                    return "";
             default:
                return QVariant();
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
                return QString("Datatype");
             case 2:
                return QString("Discription");
             default:
                return QString("Column %1").arg(section);
         }

     }else{
         return QString("Prop %1").arg(section);
     }
 }

QString btnodemodel::name() const
{
    return node->name();
}

void btnodemodel::setName(QString name)
{
    node->setName(name);
}

QString btnodemodel::description() const
{
    return node->description();
}

void btnodemodel::setDescription(QString description)
{
    node->setDescription(description);
}

QString btnodemodel::classname() const
{
    return node->className();
}

void btnodemodel::setClassname(QString classname)
{
    node->setClassName(classname);
}

#include "btnodemodel.moc"