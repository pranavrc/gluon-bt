#include <QMessageBox>

#include "bteditor.h"
#include "btbrain.h"
#include "bttreemodel.h"
#include "btavailablenodesmodel.h"
#include "btnodetypesmodel.h"

bteditor::bteditor(QWidget *parent)
{
    setupUi(this);
    setupActions();

    m_brain = new btBrain(this);
    btNodeTypesModel *nodeTypes = new btNodeTypesModel(m_brain, this);
    connect(
        m_brain, SIGNAL(nodeTypeAdded(btNodeType*)),
        nodeTypes, SLOT(newBehaviorTreeTypeAdded(btNodeType*))
        );
    connect(
        m_brain, SIGNAL(behaviorTreeAdded(btTreeModel*)),
        this, SLOT(newBehaviorTreeAdded(btTreeModel*))
        );
    this->availableNodes->setModel(nodeTypes);
    m_brain->newBehaviorTree();
}

bteditor::~bteditor()
{}

void bteditor::setupActions()
{
    connect(
        actionQuit, SIGNAL(triggered(bool)),
        qApp, SLOT(quit())
        );
    connect(
        showBehaviorTreeList, SIGNAL(clicked(bool)),
        this, SLOT(showBehaviorTreeListCicked())
        );
}

void bteditor::showBehaviorTreeListCicked()
{
    QMessageBox::about(this, this->windowTitle(), "Show list of all behavior trees... menu permayhaps?");
}

void bteditor::newBehaviorTreeAdded(btTreeModel* newTree)
{
    this->btEditor->setModel(newTree);
    this->currentBTNameLabel->setText(newTree->name());
}

#include "bteditor.moc"
