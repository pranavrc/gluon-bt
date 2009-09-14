#ifndef BTNODE_H
#define BTNODE_H

#include <QObject>
#include <QList>
#include "btdecoratornode.h"

class QString;
class QVariant;
class btNodeType;

class btNode : public QObject
{
Q_OBJECT;
Q_PROPERTY(QString name READ name WRITE setName);
Q_PROPERTY(QString description READ description WRITE setDescription);

public:
    btNode(btNodeType *type = 0, btNode *parent = 0);
    ~btNode();
    
    bool runBehavior();

	void appendChild(btNode *);
	
	btNode *child(int row);
	int childCount() const;
	int columnCount() const;
	int row() const;
	btNode *parent();
	QVariant data(int column) const;
    QVariant headerData(int column) const;
	
    void setName(QString name);
    QString name() const;
    void setDescription(QString description);
    QString description() const;
	void setType(btNodeType *newType);
	btNodeType* type() const;

    void addDecorator(btDecoratorNode* decorator);
    void removeDecorator(btDecoratorNode* decorator);
    int decoratorCount();
    QList<btDecoratorNode*> decorators() const;

private:
	btNodeType *m_type;
	
	btNode *parentNode;
	QList<btNode *> children;
	
	QString m_name;
    QString m_description;
	QList<QVariant> nodeData;
    QList<btDecoratorNode*> m_decorators;
};

#endif // BTNODE_H
