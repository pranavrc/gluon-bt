#ifndef _PROJECTPARSER_H_
#define _PROJECTPARSER_H_

#include <QObject>
#include <QHash>

class QDomNode;
class btBrain;
class btTreeModel;
class btNode;
class btNodeType;

class projectParser : public QObject
{
    Q_OBJECT

public:
    static projectParser * instance();

    //parsing the xmldata, which is a QString which is contents of the xml file
    btBrain* parseProject(QString xmlData);
    //returning the btBrain serialized to a xml formatted QString
    QString serializeProject(btBrain * brain) const;

private:
    projectParser();

    QHash<int, btTreeModel*> behaviorTreesList;

    void parseNodeTypes(QDomNode xNode, btBrain * brain);
    void parseBehaviorTrees(QDomNode xNode, btNode * node ,btBrain * brain);

    QString serializeNodeTypes(QList<btNodeType *> nodeTypes) const;
    QString serializeBehaviorTree(QList<btTreeModel *> behaviorTrees) const;
    QString serializeNodeTypeProperties(btNodeType * nodetype) const;
    QString serializeBehaviorTreeNode(btNode* node, QList<btTreeModel *> behaviorTrees) const;
    QString serializeBehaviorTreeDecorator(btNodeType * decorator) const;
};

#endif
