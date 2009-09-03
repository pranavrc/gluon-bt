#ifndef BTNODE_H
#define BTNODE_H

#include <QList>

class QString;
class QVariant;
class btNodeType;

class btNode
{
public:
    btNode(btNodeType *type = 0, btNode *parent = 0);
    ~btNode();

	void appendChild(btNode *);
	
	btNode *child(int row);
	int childCount() const;
	int columnCount() const;
	int row() const;
	btNode *parent();
	QVariant data(int column) const;
	
    void setName(QString name);
    QString name() const;
    void setDescription(QString description);
    QString description() const;
	void setType(btNodeType *newType);
	btNodeType* type() const;

private:
	btNodeType *m_type;
	
	btNode *parentNode;
	QList<btNode *> children;
	
	QString m_name;
    QString m_description;
	QList<QVariant> nodeData;
};

#endif // BTNODE_H
