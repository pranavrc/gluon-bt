#ifndef BTNODEEDITWIDGET_H
#define BTNODEEDITWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QGridLayout>
#include <QListView>

class btNodeEditWidget : public QWidget
{
public:
    btNodeEditWidget();
private:
    QVBoxLayout     *mainLayout;
    QHBoxLayout     *buttonLayout;
    QGridLayout     *editLayout;
    QLabel          *name;
    QLabel          *classname;
    QLabel          *discription;
    QLabel          *properties;
    QLineEdit       *nameedit;
    QLineEdit       *classnameedit;
    QLineEdit       *discriptionedit;
    QListView       *propertyList;

};

#endif // BTNODEEDITWIDGET_H
