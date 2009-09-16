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

#include <QBoxLayout>
#include <QVariant>
#include <QLabel>
#include <QLineEdit>
#include <QDoubleSpinBox>
#include <QGridLayout>
#include <QtCore/QMetaClassInfo>

#include "btpropertywidget.h"
#include "btnode.h"

btPropertyWidget::btPropertyWidget(QObject * parent)
{
}

btPropertyWidget::~btPropertyWidget()
{
}

void btPropertyWidget::appendToPropertyView (QGridLayout * layout, qint32 &row, QString name, QString description, QVariant value, QVariant options)
{
    ++row;
    
    QLabel * nameLabel = new QLabel(this);
    nameLabel->setText(name);
    nameLabel->setToolTip(description);
    layout->addWidget(nameLabel, row, 0);
    
    QWidget * editWidget;
    switch(value.type())
    {
        case QVariant::String:
            editWidget = new QLineEdit(this);
            qobject_cast<QLineEdit*>(editWidget)->setText(value.toString());
            break;
        case QVariant::Int:
            editWidget = new QSpinBox(this);
            qobject_cast<QSpinBox*>(editWidget)->setValue(value.toInt());
            break;
        case QVariant::Double:
            editWidget = new QDoubleSpinBox(this);
            qobject_cast<QDoubleSpinBox*>(editWidget)->setValue(value.toDouble());
            break;
        default:
            editWidget = new QLabel(this);
            qobject_cast<QLabel*>(editWidget)->setText(tr("Unknown type (%1)").arg(value.toString()));
            break;
    }
    layout->addWidget(editWidget, row, 1);
}

void btPropertyWidget::appendMetaObjectToPropertyView (QGridLayout * layout, qint32 &row, QObject * object)
{
    QString propertyName, propertyDescription;
    QVariant propertyValue;
    
    const QMetaObject *metaobject = object->metaObject();
    
    int count = metaobject->propertyCount();
    for (int i=0; i<count; ++i)
    {
        QMetaProperty metaproperty = metaobject->property(i);
        propertyName = metaproperty.name();
        if(propertyName == "objectName")
            continue;
        propertyValue = object->property(propertyName.toUtf8());
        appendToPropertyView(layout, row, propertyName, propertyDescription, propertyValue);
    }
    
    foreach(QByteArray name, object->dynamicPropertyNames())
    {
        propertyName = QString(name);
        propertyValue = object->property(name);
        appendToPropertyView(layout, row, propertyName, propertyDescription, propertyValue);
    }
}

void btPropertyWidget::appendObjectToPropertyView (QGridLayout * layout, qint32 &row, btNode * node)
{
    ++row;
    QLabel * titleLabel = new QLabel(this);
    titleLabel->setText(node->name());
    titleLabel->setToolTip(node->description());
    layout->addWidget(titleLabel, row, 0, 1, 2);
 
    // Add a new property line for each property in the object's metaobject...
    QObject *object = node;
    appendMetaObjectToPropertyView(layout, row, object);
    
}

void btPropertyWidget::appendComponentToPropertyView (QGridLayout * layout, qint32 &row, btNodeType * node)
{
    ++row;
    QLabel * titleLabel = new QLabel(this);
    titleLabel->setText(node->name());
    titleLabel->setToolTip(node->description());
    layout->addWidget(titleLabel, row, 0, 1, 2);
    
    // Add a new property line for each property in the object's metaobject...
    QObject *object = node;
    appendMetaObjectToPropertyView(layout, row, object);
}

void btPropertyWidget::setupPropertyView()
{
    QGridLayout * propertyLayout = new QGridLayout(this);
    
    qint32 row = 0;

    // First add yourself...
    appendObjectToPropertyView(propertyLayout, row, node());
    
    // Then add all the decorators...
    btDecoratorNode * decorator;
    foreach(decorator, node()->decorators())
        appendComponentToPropertyView(propertyLayout, row, decorator);
    
    // Finally, add the node's nodeType
    appendComponentToPropertyView(propertyLayout, row, node()->type());
    
    // Add spacery type stuffs...
    QWidget * containerWidget = new QWidget(this);
    containerWidget->setLayout(propertyLayout);
    
    QVBoxLayout * containerLayout = new QVBoxLayout(this);
    containerLayout->addWidget(containerWidget);
    containerLayout->addStretch();
    
    this->setLayout(containerLayout);
}

btNode * btPropertyWidget::node() const { return m_node; }
void btPropertyWidget::setNode(btNode * node) { m_node = node; setupPropertyView(); }

#include "btpropertywidget.moc"
