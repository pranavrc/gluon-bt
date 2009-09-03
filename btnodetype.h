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
    enum Category { Unusable = -1, Action = 0, Condition = 1, Composite = 2, Decorator = 3, Reference = 4 };

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
