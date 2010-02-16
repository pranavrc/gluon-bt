#ifndef _BTBRAIN_H_
#define _BTBRAIN_H_

#include <QObject>
#include <QList>
#include <QHash>
#include <QtXml/QDomDocument>
#include <QtXml/QDomNode>

#include "btlib_export.h"

class btNode;

class BT_LIB_EXPORT btBrain : public QObject
{
    Q_OBJECT
    
    Q_PROPERTY(QString name READ name WRITE setName)
    Q_PROPERTY(QString description READ description WRITE setDescription)
    
public:
    btBrain(QString data);
    ~btBrain();
    
    btNode* getBehaviorTree(int index);
    int behaviorTreesCount();
    
    QString name();
    void setName(QString name);
    QString description();
    void setDescription(QString description);
    
private:
    QHash<int, btNode*> m_behaviorTrees;
    
    QString m_name;
    QString m_description;
    
    void parseNodeTypes(QDomNode xNode);
    void parseBehaviorTrees(QDomNode xNode, btNode* node);
};

#endif
