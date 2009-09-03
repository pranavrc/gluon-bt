#ifndef BTNODETYPE_H
#define BTNODETYPE_H

#include <QObject>

class btNodeType : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name WRITE setName)
    Q_PROPERTY(QString description READ description WRITE setDescription)
    Q_PROPERTY(Category category READ category WRITE setCategory)
    Q_ENUMS(Category)

public:
    enum Category { UnusableCategory = -1, ActionCategory = 0, ConditionCategory = 1, CompositeCategory = 2, DecoratorCategory = 3, ReferenceCategory = 4 };

    btNodeType(QObject *parent = 0);
    ~btNodeType();

    void setName(QString name);
    QString name() const;
    void setDescription(QString description);
    QString description() const;
    void setCategory(Category category);
    Category category() const;

    QString categoryToString() const;
private:
    QString m_name;
    QString m_description;
    Category m_category;
};

#endif // BTNODETYPE_H
