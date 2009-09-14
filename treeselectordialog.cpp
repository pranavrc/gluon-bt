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

    model = new QStringListModel();

}

void TreeSelectorDialog::updateModel(QList<btTreeModel *> behaviortrees){
    QStringList* list = new QStringList();

    if(!behaviortrees.isEmpty()){
        foreach(btTreeModel* bttm,behaviortrees){
            list->append(bttm->name());
        }
        model->setStringList(*list);
        treelist->setModel(model);
    }else{
        qDebug("Listen er tom");
    }


}

void TreeSelectorDialog::updateModel(btTreeModel * behaviortree){

}
