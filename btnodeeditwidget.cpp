#include "btnodeeditwidget.h"
#include "btnodemodel.h"

btNodeEditWidget::btNodeEditWidget()
{
    mainLayout  = new QVBoxLayout(this);
    editLayout  = new QGridLayout();

    name        = new QLabel(tr("Name"));
    classname   = new QLabel(tr("Classname"));
    discription = new QLabel(tr("Discription"));
    properties  = new QLabel(tr("Properties"));

    nameedit        = new QLineEdit();
    classnameedit   = new QLineEdit();
    discriptionedit = new QLineEdit();

    propertyList    = new QTableView();

    editLayout->addWidget(name,0,0);
    editLayout->addWidget(nameedit,0,1);
    editLayout->addWidget(classname,0,2);
    editLayout->addWidget(classnameedit,0,3);
    editLayout->addWidget(discription,1,0);
    editLayout->addWidget(discriptionedit,1,1,1,3);

    mainLayout->addLayout(editLayout);
    mainLayout->addWidget(properties);
    mainLayout->addWidget(propertyList);

}

void btNodeEditWidget::setModel(btnodemodel* btmodel)
{
    propertyList->setModel(btmodel);
    nameedit->setText(btmodel->name());
    classnameedit->setText(btmodel->classname());
    discriptionedit->setText(btmodel->description());
}