/*
    <one line to give the program's name and a brief idea of what it does.>
    Copyright (C) <year>  <name of author>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/

#include "btpropertywidgetitem.h"
#include <QtGui>

#include "btqvariantlistwidget.h"
#include "btchildlistwidget.h"

btPropertyWidgetItem::btPropertyWidgetItem(QObject * parent, Qt::WindowFlags f)
{
    QGridLayout * layout = new QGridLayout(this);
    layout->setSpacing(0);
    layout->setMargin(0);
    this->setLayout(layout);
}

btPropertyWidgetItem::~btPropertyWidgetItem()
{
}

void btPropertyWidgetItem::setEditObject(QObject * editThis)
{
    this->editedObject = editThis;
}


void btPropertyWidgetItem::setEditProperty(QString propertyName)
{
    this->propertyName = propertyName;
    setupPropertyWidget();
}

void btPropertyWidgetItem::setupPropertyWidget()
{
    if(!editedObject)
        return;
    
    QVariant value = editedObject->property(propertyName.toUtf8());
    
    if(value.toString() == "[Child Weights]")
    {
        editWidget = createChildProbabilitiesList();
    }
    else
    {
        switch(value.type())
        {
            case QVariant::String:
                editWidget = createLineEdit(value);
                break;
            case QVariant::Int:
                editWidget = createSpinBox(value);
                break;
            case QVariant::Double:
                editWidget = createDoubleSpinBox(value);
                break;
            case QVariant::List:
                editWidget = createList(value);
                break;
            default:
                editWidget = new QLabel(this);
                qobject_cast<QLabel*>(editWidget)->setText(tr("Unknown type (%1)").arg(value.toString()));
                break;
        }
    }
    
    layout()->addWidget(editWidget);
}

void btPropertyWidgetItem::propertyChanged(QString value) { propertyChanged(QVariant(value)); }
void btPropertyWidgetItem::propertyChanged(int value) { propertyChanged(QVariant(value)); }
void btPropertyWidgetItem::propertyChanged(double value) { propertyChanged(QVariant(value)); }
void btPropertyWidgetItem::propertyChanged(QVariant value)
{
    if(!editedObject)
        return;
    
    editedObject->setProperty(propertyName.toUtf8(), value);
    
    emit sendUpdateTreeModel();
}

void btPropertyWidgetItem::QVariantListItemRemoved(QListWidgetItem * item, int index)
{
    if(!editedObject || !item)
        return;
    
    QVariant value = editedObject->property(propertyName.toUtf8());
    int typeId = QMetaType::type(editedObject->property(propertyName.toUtf8()).toString().toUtf8());
    
    QVariantList list;
    
    if(!typeId)
    {
        typeId = value.type();
        list = qvariant_cast<QVariantList>(value);
    }
    else 
    {
        list = qvariant_cast<QVariantList>(QVariant((QVariant::Type)typeId));
    }
    
    if(list.contains(item->text()))
    {
        delete item;
        list.removeAt(index);
    }
    
    editedObject->setProperty(propertyName.toUtf8(), list);
}

void btPropertyWidgetItem::QVariantListItemAdded(QListWidgetItem * item)
{
    if(!editedObject)
        return;
    
    QVariant value = editedObject->property(propertyName.toUtf8());
    int typeId = QMetaType::type(editedObject->property(propertyName.toUtf8()).toString().toUtf8());
    
    QVariantList list;
    
    if(!typeId)
    {
        typeId = value.type();
        list = qvariant_cast<QVariantList>(value);
    }
    else 
    {
        list = qvariant_cast<QVariantList>(QVariant((QVariant::Type)typeId));
    }
    list.append(item->text());
    editedObject->setProperty(propertyName.toUtf8(), list);
}

void btPropertyWidgetItem::QVariantListItemChanged(QListWidgetItem * item, int index)
{
    if(!editedObject || index < 0)
        return;
    
    QVariant value = editedObject->property(propertyName.toUtf8());
    int typeId = QMetaType::type(editedObject->property(propertyName.toUtf8()).toString().toUtf8());
    
    QVariantList list;
    
    if(!typeId)
    {
        typeId = value.type();
        list = qvariant_cast<QVariantList>(value);
    }
    else 
    {
        list = qvariant_cast<QVariantList>(QVariant((QVariant::Type)typeId));
    }
    
    list.replace(index, item->text());
    
    editedObject->setProperty(propertyName.toUtf8(), list);
}

QWidget * btPropertyWidgetItem::createLineEdit(QVariant value)
{
    QLineEdit * widget = new QLineEdit(this);
    widget->setText(value.toString());
    connect(widget, SIGNAL(textChanged(QString)), this, SLOT(propertyChanged(QString)));
    return widget;
}

QWidget * btPropertyWidgetItem::createSpinBox(QVariant value)
{
    QSpinBox * widget = new QSpinBox(this);
    widget->setValue(value.toInt());
    connect(widget, SIGNAL(valueChanged(int)), this, SLOT(propertyChanged(int)));
    return widget;
}

QWidget * btPropertyWidgetItem::createDoubleSpinBox(QVariant value)
{    
    QDoubleSpinBox * widget = new QDoubleSpinBox(this);
    widget->setValue(value.toDouble());
    connect(widget, SIGNAL(valueChanged(double)), this, SLOT(propertyChanged(double)));
    return widget;
}

QWidget * btPropertyWidgetItem::createList(QVariant value)
{
    btQVariantListWidget * widget = new btQVariantListWidget(this);
    connect(widget, SIGNAL(itemRemoved(QListWidgetItem*, int)), this, SLOT(QVariantListItemRemoved(QListWidgetItem*, int)));
    connect(widget, SIGNAL(itemAdded(QListWidgetItem*)), this, SLOT(QVariantListItemAdded(QListWidgetItem*)));
    connect(widget, SIGNAL(itemChanged(QListWidgetItem*, int)), this, SLOT(QVariantListItemChanged(QListWidgetItem*, int)));
    
    QVariantList list = qvariant_cast<QVariantList>(value);
    
    for(int i = 0; i < list.count(); i++)
    {
        QListWidgetItem * item = new QListWidgetItem(list.at(i).toString());
        item->setFlags(widget->returnItemFlags());
        widget->addItem(item);
    }
    
    return widget;
}

const QString btPropertyWidgetItem::getPropertyType(QString propertyName)
{
    return "";
}

QWidget * btPropertyWidgetItem::createChildProbabilitiesList()
{
    btChildListWidget* widget = new btChildListWidget(this);
    
    widget->setChildProbabilites(editedObject);
    
    return widget;
}

#include "btpropertywidgetitem.moc"
