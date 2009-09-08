#ifndef BTNODETYPE_H
#define BTNODETYPE_H

#include <QObject>

class btNodeType : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name WRITE setName)
    Q_PROPERTY(QString description READ description WRITE setDescription)
    Q_PROPERTY(nodeType type READ type WRITE setNodeType)
	Q_ENUMS(nodeType)
	
public:
	
	enum nodeType
	{
		UnusableNodeType = -1,
		ActionNodeType,
		CompositeNodeType,
		ConditionNodeType,
		ReferenceNodeType,
        DecoratorNodeType
	};
	
    btNodeType(QObject* parent = 0);
    ~btNodeType();

    void setName(QString name);
	QString name() const;
    void setDescription(QString description);
    QString description() const;
    nodeType type() const;
	void setNodeType(nodeType type);
	
protected:
    QString m_name;
    QString m_description;
    nodeType m_type;
};

#endif // BTNODETYPE_H
