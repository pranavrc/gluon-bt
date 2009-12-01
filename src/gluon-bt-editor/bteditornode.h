#ifndef _BTEDITORNODE_H_
#define _BTEDITORNODE_H_

#include <QObject>

#include "../gluon-bt-common/btnode.h"

class btTreeModel;

class btEditorNode : public btNode 
{
    Q_OBJECT
    
public:    
    
    btEditorNode(btNodeType *type = 0, btNode *parent = 0);
    ~btEditorNode();
    
    const QString toXml(QList<btTreeModel *> behaviorTrees);
    
    QVariant data(int column) const;
    QVariant headerData(int column) const;
    
    void addDecorator(btNodeType* decorator);
    void removeDecorator(btNodeType* decorator);
    void moveDecorator(int move, btNodeType * decorator);
    int decoratorCount() const;
    QList<btNodeType*> decorators() const;
    
Q_SIGNALS:
    void updatePropertyWidget();
    
private:    
    QList<btNodeType*> m_decorators;
};

#endif
