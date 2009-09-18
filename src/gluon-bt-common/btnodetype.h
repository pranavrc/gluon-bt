#ifndef BTNODETYPE_H
#define BTNODETYPE_H

#include <QObject>
#include <QMetaObject>
#include <QMetaProperty>

class btNodeType : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name WRITE setName)
    Q_PROPERTY(QString description READ description WRITE setDescription)
    Q_PROPERTY(nodeType type READ type WRITE setNodeType)
    Q_PROPERTY(QString className READ className WRITE setClassName )
    Q_ENUMS(nodeType)

public:

    enum nodeType
    {
        UnusableNodeType = 0,
        ActionNodeType,
        CompositeNodeType,
        ConditionNodeType,
        ReferenceNodeType,
        DecoratorNodeType
    };

    btNodeType(QObject* parent = 0);
    ~btNodeType();

    virtual void setName(QString name);
    virtual QString name() const;
    virtual void setDescription(QString description);
    virtual QString description() const;
    virtual nodeType type() const;

    virtual void setNodeType(nodeType type);
    virtual bool run();
    virtual btNodeType * copy();
    virtual QString className() const;
    virtual void setClassName(QString className);

protected:
    QString m_name;
    QString m_description;
    QString m_className;
    nodeType m_type;
};

#endif // BTNODETYPE_H