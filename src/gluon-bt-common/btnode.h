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

	virtual void appendChild(btNode *);
	
	virtual btNode *child(int row);
	virtual int childCount() const;
	virtual int columnCount() const;
	virtual int row() const;
	virtual btNode *parent();
    virtual void setParentNode(btNode * node);
	virtual QVariant data(int column) const;
    virtual QVariant headerData(int column) const;
	
    virtual void setName(QString name);
    virtual QString name() const;
    virtual void setDescription(QString description);
    virtual QString description() const;
	virtual void setType(btNodeType *newType);
    virtual btNodeType* type() const;

    virtual void addDecorator(btDecoratorNode* decorator);
    virtual void removeDecorator(btDecoratorNode* decorator);
    virtual int decoratorCount();
    QList<btDecoratorNode*> decorators() const;


private:
	btNodeType *m_type;
	
	btNode *parentNode;
    QList<btNode *> m_children;
	
	QString m_name;
    QString m_description;
	QList<QVariant> nodeData;
    QList<btDecoratorNode*> m_decorators;
};

#endif // BTNODE_H
