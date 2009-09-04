#ifndef bteditor_H
#define bteditor_H

#include <QtGui/QMainWindow>
#include "ui_bteditor.h"

class btBrain;
class btTreeModel;

class bteditor : public QMainWindow, private Ui::BtEditor
{
Q_OBJECT
public:
    bteditor(QWidget *parent = 0);
    virtual ~bteditor();
    void setupActions();

public Q_SLOTS:
    void newBehaviorTreeAdded(btTreeModel* newTree);
    void showBehaviorTreeListCicked();
    
private:
    btBrain *m_brain;
    btTreeModel *m_currentBehaviorTree;
};

#endif // bteditor_H
