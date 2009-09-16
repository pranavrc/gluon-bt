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

#ifndef BTPROPERTYWIDGET_H
#define BTPROPERTYWIDGET_H

#include <QtGui/QWidget>
class btNode;
class btNodeType;
class QGridLayout;
class btDecoratorNode;

class btPropertyWidget : public QWidget
{
Q_OBJECT;

public:
    btPropertyWidget(QObject * parent = 0);
    ~btPropertyWidget();
    
    btNode * node() const;
    void setNode(btNode * theNode);
    
private:
    btNode * m_node;
    
    QWidget * createComponentPropertyView();
    
    void setupPropertyView();
    void appendToPropertyView (QGridLayout *layout, qint32 &row, QString name, QString descrition, QVariant value, QVariant options = 0);
    void appendObjectToPropertyView (QGridLayout * layout, qint32 &row, btNode * node);
    void appendComponentToPropertyView (QGridLayout *layout, qint32 &row, btNodeType * node);
    void appendMetaObjectToPropertyView (QGridLayout * layout, qint32 &row, QObject * object);
};

#endif // BTPROPERTYWIDGET_H
