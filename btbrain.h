#ifndef BTBRAIN_H
#define BTBRAIN_H

#include <QObject>

class btNodeType;
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
    btNodeType *findNodeTypeByName(QString name);
    
    QList<btNodeType *> nodeTypes;
    QList<btTreeModel *> behaviorTrees;
    
    void setName(QString name);
    QString name() const;
Q_SIGNALS:
    void behaviorTreeAdded(btTreeModel* newTree);
    void nodeTypeAdded(btNodeType* newNodeType);

private:
    QString m_name;
};

#endif // BTBRAIN_H
