#include <QtGui>

#include "btqlistdelegate.h"
btQListDeletgate::btQListDeletgate(QObject *parent)
: QItemDelegate(parent)
{
}

QWidget *btQListDeletgate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QComboBox *comboBox = new QComboBox(parent);
    comboBox->addItem("int", QVariant("int"));
    comboBox->addItem("QString", QVariant("QString"));
    comboBox->addItem("double", QVariant("double"));
    comboBox->addItem("QVariantList", QVariant("QVariantList"));
    comboBox->setCurrentIndex(comboBox->findData(index.data()));
    return comboBox;
}

void btQListDeletgate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    QString value = index.model()->data(index, Qt::EditRole).toString();
    
    QComboBox *comboBox = static_cast<QComboBox*>(editor);
    comboBox->setCurrentIndex(comboBox->findData(value));
}

void btQListDeletgate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    QComboBox *spinBox = static_cast<QComboBox*>(editor);
    QString value = spinBox->currentText();
    model->setData(index, value, Qt::EditRole);
}

void btQListDeletgate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &/* index */) const
{
    editor->setGeometry(option.rect);
}

#include "btqlistdelegate.moc"