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

void btPropertyWidget::appendToPropertyView (QGridLayout * layout, qint32 row, QString name, QString description, QVariant value, QVariant options)
{
    ++row;
    
    QLabel * nameLabel = new QLabel(this);
    nameLabel->setText(name);
    nameLabel->setToolTip(description);
    layout->addWidget(nameLabel, row, 0);
    
    switch(value.type())
    {
    }
}

void btPropertyWidget::appendObjectToPropertyView (QGridLayout * layout, qint32 row, btNode * node)
{
    QString propertyName, propertyDescription;
    QVariant propertyValue;
    
    QLabel * titleLabel = new QLabel(this);
    titleLabel->setText(node->name());
    titleLabel->setToolTip(node->description());
    layout->addWidget(titleLabel, 0, row, 2, 0);
    
    // Add a new property line for each property in the object's metaobject...
    QObject *object = this->m_node;
    const QMetaObject *metaobject = object->metaObject();
    int count = metaobject->propertyCount();
    for (int i=0; i<count; ++i)
    {
        QMetaProperty metaproperty = metaobject->property(i);
        propertyName = metaproperty.name();
        propertyValue = object->property(propertyName);
        appendToPropertyView(layout, row, propertyName, propertyDescription, propertyValue);
    }
}

void btPropertyWidget::setupPropertyView()
{
    QGridLayout * propertyLayout = new QGridLayout(this);
    
    qint32 row = 0;

    appendObjectToPropertyView(propertyLayout, row, m_node);
    
    //foreach()
    
    this->setLayout(propertyLayout);
}

btNode * btPropertyWidget::node() const { return m_node; }
void btPropertyWidget::setNode(btNode * node) { m_node = node; setupPropertyView(); }

#include "btpropertywidget.moc"
