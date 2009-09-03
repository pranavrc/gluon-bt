#include "btnodetype.h"

btNodeType::btNodeType(QObject *parent)
{
}

btNodeType::~btNodeType()
{
}

QString btNodeType::categoryToString() const
{
    switch(category())
    {
        case btNodeType::ActionCategory:
            return tr("Action");
            break;
        case btNodeType::CompositeCategory:
            return tr("Composite");
            break;
        case btNodeType::ConditionCategory:
            return tr("Condition");
            break;
        case btNodeType::DecoratorCategory:
            return tr("Decorator");
            break;
        case btNodeType::ReferenceCategory:
            return tr("Reference");
            break;
        default:
            return tr("Unknown!");
            break;
    }
    return tr("Impossible Result");
}

void btNodeType::setName(QString name) { m_name = name; }
QString btNodeType::name() const { return m_name; }

void btNodeType::setDescription(QString description) { m_description = description; }
QString btNodeType::description() const { return m_description; }

void btNodeType::setCategory(Category category) { m_category = category; }
btNodeType::Category btNodeType::category() const { return m_category; }

#include "btnodetype.moc"
