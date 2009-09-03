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
        case btNodeType::Action:
            return tr("Action");
            break;
        case btNodeType::Composite:
            return tr("Composite");
            break;
        case btNodeType::Condition:
            return tr("Condition");
            break;
        case btNodeType::Decorator:
            return tr("Decorator");
            break;
        case btNodeType::Reference:
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
