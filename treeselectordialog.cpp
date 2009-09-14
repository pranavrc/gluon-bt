#include "treeselectordialog.h"

TreeSelectorDialog::TreeSelectorDialog()
{
    // layout
    this->setWindowTitle(tr("Select Tree"));
    mainLayout = new QVBoxLayout(this);
    buttonLayout = new QHBoxLayout;
    treelist = new QListView();
    cancel_button = new QPushButton(tr("Cancel"));
    ok_button = new QPushButton(tr("Ok"));
    buttonLayout->addStretch();
    buttonLayout->addWidget(ok_button);
    buttonLayout->addWidget(cancel_button);
    mainLayout->addWidget(treelist);
    mainLayout->addLayout(buttonLayout);
    this->setLayout(mainLayout);

    setupActions();

    list = new QStringList();
    model = new QStringListModel();
    model->setStringList(*list);
    treelist->setModel(model);
}

void TreeSelectorDialog::setupActions(){
    connect(
        ok_button, SIGNAL(clicked(bool)),
        this, SLOT(chooseTree())
        );
    connect(
        cancel_button, SIGNAL(clicked(bool)),
        this, SLOT(reject())
        );
}

void TreeSelectorDialog::updateModel(QList<btTreeModel *> behaviortrees){
    if(!behaviortrees.isEmpty()){
        list->clear();
        foreach(btTreeModel* bttm,behaviortrees){
            list->append(bttm->name());
        }
        model->setStringList(*list);
    }else{
        qDebug("List is empty");
    }
}

void TreeSelectorDialog::updateModel(btTreeModel * behaviortree){
    list->append(behaviortree->name());
    model->setStringList(*list);
}

void TreeSelectorDialog::chooseTree(){
    qDebug("set tree to whatever was selected");
    emit TreeSelectorDialog::accept();
}

#include "treeselectordialog.moc"
