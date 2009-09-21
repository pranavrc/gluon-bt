#include "btnodemodel.h"
#include "btnodetypesmodel.h"
#include "bteditornodetype.h"
#include <QDebug>

btnodemodel::btnodemodel(btEditorNodeType * nodetype,QObject *parent)
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

Qt::ItemFlags btnodemodel::flags(const QModelIndex &index) const
{
    if(!index.isValid()){
        return Qt::ItemIsEnabled;
    }
    return QAbstractItemModel::flags(index) | Qt::ItemIsEditable;
}

bool btnodemodel::setData(const QModelIndex &index,
                          const QVariant &value,int role)
{
    if(index.isValid() && role == Qt::EditRole){
        QString newName = value.toString();
        QString oldName = node->dynamicPropertyNames().at(index.row());
        if(newName != ""){
            if(index.column() == 0){
                node->setProperty(newName.toUtf8(),node->property(oldName.toUtf8()));
                node->setProperty(oldName.toUtf8(),QVariant::Invalid);
            }else if(index.column() == 1){
                node->setProperty(oldName.toUtf8(),newName);
            }
            emit dataChanged(index,index);
            return true;
        }
    }
    return false;
}

bool btnodemodel::insertRows(int position, int rows, const QModelIndex &parent)
{
    beginInsertRows(QModelIndex(), position, position+rows-1);
    node->setProperty((tr("newProperty") + QString::number(position)).toUtf8(),"QString");

    endInsertRows();
    return true;
}

 bool btnodemodel::removeRows(int position, int rows, const QModelIndex &parent)
 {
     beginRemoveRows(QModelIndex(), position, position+rows-1);

    if(node->dynamicPropertyNames().count() > position){
        QString propertyName = node->dynamicPropertyNames().at(position);
        node->setProperty(propertyName.toUtf8(),QVariant::Invalid);
    }

     endRemoveRows();
     return true;
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
