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
#include <QToolButton>
#include <QDebug>
#include <QMenu>
#include <QAction>

#include "btpropertywidget.h"
#include "btpropertywidgetitem.h"
#include "bteditornode.h"
#include "bteditornodetype.h"
#include "colorgen.h"

btPropertyWidget::btPropertyWidget(QObject * parent)
{
    colorgen = NULL;
    m_node = NULL;
}

btPropertyWidget::~btPropertyWidget()
{
    delete colorgen;
}

void btPropertyWidget::appendToPropertyView (QGridLayout * layout, qint32 &row, QObject * object, QString name, QString description, QVariant options)
{
    ++row;
    
    QLabel * nameLabel = new QLabel(this);
    nameLabel->setText(name);
    nameLabel->setToolTip(description);
    layout->addWidget(nameLabel, row, 0);
    nameLabel->setAlignment(Qt::AlignTop);
    
    btPropertyWidgetItem * editWidget = new btPropertyWidgetItem(this);
    connect(editWidget,SIGNAL(sendUpdateTreeModel()), this, SLOT(updateTreeModel()));
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
        propertyDescription = getPropertyDescription(object, propertyName);
        appendToPropertyView(layout, row, object, propertyName, propertyDescription);
    }
    
    foreach(QByteArray name, object->dynamicPropertyNames())
    {
        propertyName = QString(name);
        propertyValue = object->property(name);
        propertyDescription = getPropertyDescription(object, propertyName);;
        appendToPropertyView(layout, row, object, propertyName, propertyDescription);
    }
}

void btPropertyWidget::appendObjectToPropertyView (QGridLayout * layout, qint32 &row, btEditorNode * node)
{
    ++row;
    QLabel * titleLabel = new QLabel(this);
    titleLabel->setText(node->name());
    titleLabel->setToolTip(node->description());
    titleLabel->setStyleSheet("background-color: " + colorgen->nextColor().name());
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
    titleLabel->setStyleSheet("background-color: " + colorgen->nextColor().name());
    if(QString(node->metaObject()->className()) == "btDecoratorNode")
    {
        QHBoxLayout * hLayout = new QHBoxLayout(this);
        hLayout->addWidget(titleLabel);
        
        QAction * removeAction = new QAction(node);
        removeAction->setText("Remove");
        connect(removeAction, SIGNAL(triggered()), this, SLOT(removeActionTriggered()));
        
        QMenu * buttonMenu = new QMenu(this);
        buttonMenu->addAction(removeAction);
        
        QToolButton * showMenuButton = new QToolButton(this);
        showMenuButton->setText("Menu");
        showMenuButton->setMenu(buttonMenu);
        showMenuButton->setPopupMode(QToolButton::InstantPopup);
        
        hLayout->addWidget(showMenuButton);
        layout->addLayout(hLayout, row, 0,1,2);
    }
    else
    {
        layout->addWidget(titleLabel, row, 0, 1, 2);
    }
    
    // Add a new property line for each property in the object's metaobject...
    QObject *object = node;
    appendMetaObjectToPropertyView(layout, row, object);
}

void btPropertyWidget::setupPropertyView()
{
    qDeleteAll(this->children());
    colorgen = new ColorGen(0,70,30);
    
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
void btPropertyWidget::setNode(btEditorNode * node)
{ 
    m_node = node; 
    setupPropertyView(); 
}

QString btPropertyWidget::getPropertyDescription(QObject *object, QString propertyName)
{
    btEditorNodeType * node = qobject_cast<btEditorNodeType*>(object);
    
    if(node == NULL)
        return "";
    
    return node->getPropertyDescription(propertyName);
}

void btPropertyWidget::removeActionTriggered()
{
    m_node->removeDecorator((btNodeType*)QObject::sender()->parent());
    setupPropertyView();
    emit treeModelUpdate();
}

void btPropertyWidget::dragDropUpdate()
{
    if(m_node != NULL)
        setupPropertyView();
}

void btPropertyWidget::updateTreeModel()
{
    emit treeModelUpdate();
}

#include "btpropertywidget.moc"
