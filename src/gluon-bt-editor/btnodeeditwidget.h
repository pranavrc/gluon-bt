#ifndef BTNODEEDITWIDGET_H
#define BTNODEEDITWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QGridLayout>
#include <QTableView>
#include <QPushButton>

class btnodemodel;


class btNodeEditWidget : public QWidget
{
    Q_OBJECT


public:
    btNodeEditWidget(QWidget * parent);
    ~btNodeEditWidget();
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
    QPushButton     *remove_button;
    QPushButton     *add_button;
    btnodemodel     *model;

public Q_SLOTS:
    void nameEdited(QString name);
    void classnameEdited(QString classname);
    void descriptionEdited(QString description);
    void add_button_clicked();
    void remove_button_clicked();

};

#endif // BTNODEEDITWIDGET_H
