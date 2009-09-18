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
    Q_OBJECT
public:
    btNodeEditWidget(QWidget * parent);
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
    btnodemodel     *model;

public Q_SLOTS:
    void nameEdited(QString name);
    void classnameEdited(QString classname);
    void descriptionEdited(QString description);

};

#endif // BTNODEEDITWIDGET_H
