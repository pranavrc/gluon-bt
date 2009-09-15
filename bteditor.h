#ifndef bteditor_H
#define bteditor_H

#include <QtGui/QMainWindow>
#include "ui_bteditor.h"
#include "treeselectordialog.h"

class btBrain;
class btTreeModel;
class btNode;
class TreeSelectorDialog;

class bteditor : public QMainWindow, private Ui::BtEditor
{
Q_OBJECT
public:
    bteditor(QWidget *parent = 0);
    virtual ~bteditor();
    void setupActions();
    
    void showBehaviorTree(btTreeModel* showThis);
    void showPropertiesFor(btNode* showFor);
    
public Q_SLOTS:
    void createNewBehaviorTree();
    void newBehaviorTreeAdded(btTreeModel* newTree);
    void showBehaviorTreeListCicked();
    void setBehaviorTree(int index);
    
    void editorSelectionChanged(const QItemSelection& selected, const QItemSelection& deselected);
    
private:
    btBrain *m_brain;
    btTreeModel *m_currentBehaviorTree;
    TreeSelectorDialog *treeSelectDialog;

private slots:
    void on_actionSave_As_triggered();
    void on_actionOpen_triggered();
};

#endif // bteditor_H
