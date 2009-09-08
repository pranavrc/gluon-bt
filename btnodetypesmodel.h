#ifndef BTNODETYPESMODEL_H
#define BTNODETYPESMODEL_H

#include <QAbstractListModel>
#include <QList>
class btBrain;
class btNodeType;
class btNodeTypesModelNode;

class btNodeTypesModel : public QAbstractItemModel
{
Q_OBJECT
public:
    btNodeTypesModel(btBrain *brain, QObject *parent = 0);
    ~btNodeTypesModel();

    QMimeData* mimeData(const QModelIndexList &indexes) const;
    QStringList mimeTypes() const;
    Qt::DropActions supportedDropActions() const;
    
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;

    QModelIndex index(int row, int column, const QModelIndex &parent) const;
    QModelIndex parent(const QModelIndex &child) const;

    int rowCount(const QModelIndex &index) const;
    int columnCount(const QModelIndex &index) const;
    
public Q_SLOTS:
    void newBehaviorTreeTypeAdded(btNodeType* newType);

private:
    btNodeType *nodeTypeFromIndex(const QModelIndex &index) const;
    btNodeTypesModelNode* rootNode;
    
    btNodeTypesModelNode *nodeAction;
    btNodeTypesModelNode *nodeCondition;
    btNodeTypesModelNode *nodeComposite;
    btNodeTypesModelNode *nodeDecorator;
    btNodeTypesModelNode *nodeReference;
};

#endif // BTNODETYPESMODEL_H
