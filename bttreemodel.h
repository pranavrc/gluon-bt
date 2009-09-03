#ifndef BTTREEMODEL_H
#define BTTREEMODEL_H

#include <QObject>
#include <QAbstractItemModel>
#include <QString>
class btNode;

class btTreeModel : public QAbstractItemModel
{
    Q_OBJECT
	Q_PROPERTY(QString name READ name WRITE setName)

public:
    btTreeModel(QObject *parent = 0);
    ~btTreeModel();

    void setRootNode(btNode *newRoot);

    QModelIndex index(int row, int column, const QModelIndex &parent) const;
    QModelIndex parent(const QModelIndex &child) const;

    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    QVariant data(const QModelIndex &index, int role) const;

    QString name() const;
    void setName(QString name);
private:
	QString m_name;
	
    btNode *nodeFromIndex(const QModelIndex &index) const;

    btNode *rootNode;
};

#endif // BTTREEMODEL_H
