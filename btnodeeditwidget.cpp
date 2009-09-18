#include "btnodeeditwidget.h"
#include "btnodemodel.h"

btNodeEditWidget::btNodeEditWidget(QWidget * parent)
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

    connect(nameedit, SIGNAL(textChanged(QString)), this, SLOT(nameEdited(QString)));
    connect(classnameedit, SIGNAL(textChanged(QString)), this, SLOT(classnameEdited(QString)));
    connect(discriptionedit, SIGNAL(textChanged(QString)), this, SLOT(descriptionEdited(QString)));

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
    delete model;
    model = btmodel;

    propertyList->setModel(model);
    nameedit->setText(model->name());
    classnameedit->setText(model->classname());
    discriptionedit->setText(model->description());
}

void btNodeEditWidget::nameEdited(QString name){
    model->setName(name);
}

void btNodeEditWidget::classnameEdited(QString classname){
    model->setClassname(classname);
}

void btNodeEditWidget::descriptionEdited(QString description){
    model->setDescription(description);
}

#include "btnodeeditwidget.moc"
