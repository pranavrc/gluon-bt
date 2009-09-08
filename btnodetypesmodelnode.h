#ifndef BTNODETYPESMODELNODE_H
#define BTNODETYPESMODELNODE_H

#include <QVariant>
#include <QList>
#include <QString>
class btNodeType;

class btNodeTypesModelNode
{
public:
    btNodeTypesModelNode(btNodeType *data = 0, btNodeTypesModelNode *parent = 0);
    ~btNodeTypesModelNode();

    void appendChild(btNodeTypesModelNode *child);
    btNodeTypesModelNode *child(int row);
    int childCount() const;
    int columnCount() const;
    QVariant data(int column) const;
    int row() const;
    btNodeTypesModelNode *parent();

    btNodeType *nodeType() const;
    void setNodeType(btNodeType *nodeType);

    void setName(QString name);
    QString name() const;
    
private:
    QString m_name;
    btNodeType *nodeData;
    QList<btNodeTypesModelNode *> children;
    btNodeTypesModelNode *parentNode;
};

#endif // BTNODETYPESMODELNODE_H
