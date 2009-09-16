#ifndef BTNODEEDITWIDGET_H
#define BTNODEEDITWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QGridLayout>
#include <QTableView>

class btnodemodel;


class btNodeEditWidget : public QWidget
{
public:
    btNodeEditWidget();
    void setModel(btnodemodel* btmodel);
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
    QTableView      *propertyList;

};

#endif // BTNODEEDITWIDGET_H
