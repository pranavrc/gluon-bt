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
    
    const QString toXml(QList<btTreeModel *> behaviorTrees);    
};

#endif
