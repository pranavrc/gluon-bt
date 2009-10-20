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
#include "btpropertywidgetitem.h"
#include "bteditornode.h"
#include "bteditornodetype.h"

btPropertyWidget::btPropertyWidget(QObject * parent)
{
}

btPropertyWidget::~btPropertyWidget()
{
}

void btPropertyWidget::appendToPropertyView (QGridLayout * layout, qint32 &row, QObject * object, QString name, QString description, QVariant options)
{
    ++row;
    
    QLabel * nameLabel = new QLabel(this);
    nameLabel->setText(name);
    nameLabel->setToolTip(description);
    layout->addWidget(nameLabel, row, 0);
    
    btPropertyWidgetItem * editWidget = new btPropertyWidgetItem(this);
    editWidget->setEditObject(object);
    editWidget->setEditProperty(name);
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
        appendToPropertyView(layout, row, object, propertyName, propertyDescription);
    }
    
    foreach(QByteArray name, object->dynamicPropertyNames())
    {
        propertyName = QString(name);
        propertyValue = object->property(name);
        appendToPropertyView(layout, row, object, propertyName, propertyDescription);
    }
}

void btPropertyWidget::appendObjectToPropertyView (QGridLayout * layout, qint32 &row, btEditorNode * node)
{
    ++row;
    QLabel * titleLabel = new QLabel(this);
    titleLabel->setText(node->name());
    titleLabel->setToolTip(node->description());
    titleLabel->setStyleSheet("background-color: rgb(178, 232, 255);");
    layout->addWidget(titleLabel, row, 0, 1, 2);
 
    // Add a new property line for each property in the object's metaobject...
    QObject *object = node;
    appendMetaObjectToPropertyView(layout, row, object);
    
}

void btPropertyWidget::appendComponentToPropertyView (QGridLayout * layout, qint32 &row, btEditorNodeType * node)
{
    ++row;
    QLabel * titleLabel = new QLabel(this);
    titleLabel->setText(node->name());
    titleLabel->setToolTip(node->description());
    titleLabel->setStyleSheet("background-color: rgb(255, 220, 220);");
    layout->addWidget(titleLabel, row, 0, 1, 2);
    
    // Add a new property line for each property in the object's metaobject...
    QObject *object = node;
    appendMetaObjectToPropertyView(layout, row, object);
}

void btPropertyWidget::setupPropertyView()
{
    QGridLayout * propertyLayout = new QGridLayout(this);
    propertyLayout->setMargin(0);
    propertyLayout->setSpacing(0);
    
    qint32 row = 0;

    // First add yourself...
    appendObjectToPropertyView(propertyLayout, row, this->node());
    
    // Then add all the decorators...
    for(int i = 0; i < this->node()->decoratorCount(); i++)
    {
        appendComponentToPropertyView(propertyLayout, row, qobject_cast<btEditorNodeType*>(this->node()->decorators()[i]));
    }
    
    // Finally, add the node's nodeType
    appendComponentToPropertyView(propertyLayout, row, qobject_cast<btEditorNodeType*>(node()->type()));
    
    // Add spacery type stuffs...
    QWidget * containerWidget = new QWidget(this);
    containerWidget->setLayout(propertyLayout);
    
    QVBoxLayout * containerLayout = new QVBoxLayout(this);
    containerLayout->addWidget(containerWidget);
    containerLayout->addStretch();
    containerLayout->setSpacing(0);
    containerLayout->setMargin(0);
    
    this->setLayout(containerLayout);
}

btEditorNode * btPropertyWidget::node() const { return m_node; }
void btPropertyWidget::setNode(btEditorNode * node) { m_node = node; setupPropertyView(); }

#include "btpropertywidget.moc"
