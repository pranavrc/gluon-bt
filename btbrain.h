#ifndef BTBRAIN_H
#define BTBRAIN_H

#include <QObject>

class btEditorNodeType;
class btTreeModel;

class btBrain : public QObject
{
    Q_OBJECT;
    Q_PROPERTY(QString name READ name WRITE setName);

public:
    btBrain(QObject *parent = 0);
    ~btBrain();
    
    btTreeModel *newBehaviorTree();
    void deleteBehaviorTree(btTreeModel *behaviorTree);
    btEditorNodeType *findNodeTypeByName(QString name);
    
    QList<btEditorNodeType *> nodeTypes;
    QList<btTreeModel *> behaviorTrees;
    
    void setName(QString name);
    QString name() const;

    void addBehaviorTree(btTreeModel * newTree);
    void addNodeType(btEditorNodeType * newNodeType);
Q_SIGNALS:
    void behaviorTreeAdded(btTreeModel* newTree);
    void nodeTypeAdded(btEditorNodeType* newNodeType);

private:
    QString m_name;
};

#endif // BTBRAIN_H
