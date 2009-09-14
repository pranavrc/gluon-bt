#ifndef TREESELECTORDIALOG_H
#define TREESELECTORDIALOG_H

#include <QDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QListView>
#include <QPushButton>
#include <QStringListModel>

#include "bttreemodel.h"

class TreeSelectorDialog : public QDialog
{
    Q_OBJECT
public:
    TreeSelectorDialog();
    void updateModel(QList<btTreeModel *> behaviortrees);
    void updateModel(btTreeModel * behaviortree);
    void setupActions();

public Q_SLOTS:
    void chooseTree();

private:
    QVBoxLayout*        mainLayout;
    QHBoxLayout*        buttonLayout;
    QListView*          treelist;
    QPushButton*        cancel_button;
    QPushButton*        ok_button;
    QStringListModel*   model;
    QStringList*        list;
};

#endif // TREESELECTORDIALOG_H
