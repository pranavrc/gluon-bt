#ifndef BTNODEMODEL_H
#define BTNODEMODEL_H

#include <QAbstractTableModel>
#include <QVariant>
#include <QModelIndex>
#include "btnodetype.h"

class btnodemodel : public QAbstractTableModel
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name WRITE setName)
    Q_PROPERTY(QString description READ description WRITE setDescription)
    Q_PROPERTY(QString classname READ classname WRITE setClassname)

public:
    btnodemodel(btNodeType * nodetype,QObject *parent = 0);
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section,Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const;

    QString name() const;
    void setName(QString name);

    QString description() const;
    void setDescription(QString description);

    QString classname() const;
    void setClassname(QString classname);

private:
    btNodeType *     node;
};

#endif // BTNODEMODEL_H
