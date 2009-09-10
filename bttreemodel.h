#ifndef BTTREEMODEL_H
#define BTTREEMODEL_H

#include <QObject>
#include <QAbstractItemModel>
#include <QString>
class btNode;
class btBrain;

class btTreeModel : public QAbstractItemModel
{
    Q_OBJECT
	Q_PROPERTY(QString name READ name WRITE setName)

public:
    btTreeModel(QObject *parent = 0, btBrain* containingBrain = 0);
    ~btTreeModel();

    void setRootNode(btNode *newRoot);
    btNode * rootNode() const;

    QModelIndex index(int row, int column, const QModelIndex &parent) const;
    QModelIndex parent(const QModelIndex &child) const;

    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    QVariant data(const QModelIndex &index, int role) const;
    bool setData ( const QModelIndex & index, const QVariant & value, int role = Qt::EditRole );
    
    Qt::ItemFlags flags(const QModelIndex &index) const;
    QStringList mimeTypes() const;
    bool dropMimeData(const QMimeData *data, Qt::DropAction action, int row, int column, const QModelIndex &parent);

    QString name() const;
    void setName(QString name);
private:
	QString m_name;
	
    btNode *nodeFromIndex(const QModelIndex &index) const;

    btNode *m_rootNode;
    btBrain *brain;
};

#endif // BTTREEMODEL_H
