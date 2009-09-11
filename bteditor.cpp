#include <QMessageBox>

#include "bteditor.h"
#include "btbrain.h"
#include "bttreemodel.h"
#include "btnodetypesmodel.h"
#include "btnode.h"

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
        actionNew_Tree, SIGNAL(triggered(bool)),
        this, SLOT(createNewBehaviorTree())
        );
    connect(
        actionQuit, SIGNAL(triggered(bool)),
        qApp, SLOT(quit())
        );
    connect(
        showBehaviorTreeList, SIGNAL(clicked(bool)),
        this, SLOT(showBehaviorTreeListCicked())
        );
    connect(
        this->btEditor->selectionModel(), SIGNAL(selectionChanged(QItemSelection,QItemSelection)),
        this, SLOT(editorSelectionChanded(QItemSelection,QItemSelection))
        );
}

void bteditor::showBehaviorTree(btTreeModel* showThis)
{
    this->btEditor->setModel(showThis);
    this->currentBTNameLabel->setText(showThis->name());
}

void bteditor::editorSelectionChanded(const QItemSelection& selected, const QItemSelection& deselected)
{
    btNode* selectedNode = static_cast<btNode*>(btEditor->selectionModel()->currentIndex().internalPointer());
    showPropertiesFor(selectedNode);
}

void bteditor::showPropertiesFor(btNode* showFor)
{
    QMessageBox::about(0, "blab", showFor->name());
}

void bteditor::createNewBehaviorTree()
{
    m_brain->newBehaviorTree();
}

void bteditor::showBehaviorTreeListCicked()
{
    QMessageBox::about(this, this->windowTitle(), "Show list of all behavior trees... menu permayhaps?");
}

void bteditor::newBehaviorTreeAdded(btTreeModel* newTree)
{
    showBehaviorTree(newTree);
}

#include "bteditor.moc"
