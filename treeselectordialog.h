#ifndef TREESELECTORDIALOG_H
#define TREESELECTORDIALOG_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QListView>
#include <QPushButton>
#include <QStringListModel>

#include "bttreemodel.h"

class TreeSelectorDialog : public QWidget
{
public:
    TreeSelectorDialog();
    void updateModel(QList<btTreeModel *> behaviortrees);
    void updateModel(btTreeModel * behaviortree);

private:
    QVBoxLayout*        mainLayout;
    QHBoxLayout*        buttonLayout;
    QListView*          treelist;
    QPushButton*        cancel_button;
    QPushButton*        ok_button;
    QStringListModel*   model;
};

#endif // TREESELECTORDIALOG_H
