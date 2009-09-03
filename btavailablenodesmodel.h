#ifndef BTAVAILABLENODESMODEL_H
#define BTAVAILABLENODESMODEL_H

#include <QMap>
#include <QAbstractProxyModel>
#include "btnodetypesmodel.h"
#include "btnodetype.h"

class btAvailableNodesModel : public QAbstractProxyModel
{
    Q_OBJECT

public:
    btAvailableNodesModel(QObject *parent = 0);

    virtual QModelIndex mapFromSource(const QModelIndex &sourceIndex) const;
    virtual QModelIndex mapToSource(const QModelIndex &proxyIndex) const;

    virtual QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const;
    virtual QModelIndex parent(const QModelIndex &child) const;

    virtual int rowCount(const QModelIndex &parent) const;
    virtual int columnCount(const QModelIndex &parent) const;
    virtual QVariant data(const QModelIndex &proxyIndex, int role) const;
private:
    QMap<int, QString> categories;
};

#endif // BTAVAILABLENODESMODEL_H
