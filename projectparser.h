#ifndef _PROJECTPARSER_H_
#define _PROJECTPARSER_H_

#include <QObject>
#include <QHash>

class btBrain;
class QDomNode;
class btNode;

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
};

#endif
