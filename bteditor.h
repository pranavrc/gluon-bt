#ifndef bteditor_H
#define bteditor_H

#include <QtGui/QMainWindow>
#include "ui_bteditor.h"
#include "treeselectordialog.h"

class btNodeTypesModel;
class btBrain;
class btTreeModel;
class btEditorNode;
class TreeSelectorDialog;
class btPropertyWidget;

class bteditor : public QMainWindow, private Ui::BtEditor
{
Q_OBJECT
public:
    bteditor(QWidget *parent = 0);
    virtual ~bteditor();
    void setupActions();
    
    void showBehaviorTree(btTreeModel* showThis);
    void showPropertiesFor(btEditorNode* showFor);
    
public Q_SLOTS:
    void createNewBehaviorTree();
    void newBehaviorTreeAdded(btTreeModel* newTree);
    void showBehaviorTreeListCicked();
    void setBehaviorTree(int index);
    void replaceBrain();
    void editorSelectionChanged(const QItemSelection& selected, const QItemSelection& deselected);
    
private:
    btBrain *m_brain;
    btNodeTypesModel* nodeTypes;
    btTreeModel *m_currentBehaviorTree;
    TreeSelectorDialog *treeSelectDialog;
    btPropertyWidget *propertyWidget;

private slots:
    void on_availableNodes_activated(QModelIndex index);
    void on_actionEdit_Node_triggered();
    void on_actionSave_As_triggered ();
    void on_actionOpen_triggered ();
};

#endif // bteditor_H
