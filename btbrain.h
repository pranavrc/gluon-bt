#ifndef BTBRAIN_H
#define BTBRAIN_H

#include <QObject>

class btNodeType;
class btTreeModel;

class btBrain : public QObject
{
    Q_OBJECT

public:
    btBrain(QObject *parent = 0);
    ~btBrain();
    
    btTreeModel *newBehaviorTree();
    void deleteBehaviorTree(btTreeModel *behaviorTree);
    btNodeType *findNodeTypeByName(QString name);
    
    QList<btNodeType *> nodeTypes;
    QList<btTreeModel *> behaviorTrees;
    
Q_SIGNALS:
    void behaviorTreeAdded(btTreeModel* newTree);
    void nodeTypeAdded(btNodeType* newNodeType);
};

#endif // BTBRAIN_H
