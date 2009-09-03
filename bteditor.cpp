#include "bteditor.h"
#include "btbrain.h"
#include "btavailablenodesmodel.h"
#include "btnodetypesmodel.h"

bteditor::bteditor(QWidget *parent)
{
    setupUi(this);
    setupActions();

    brain = new btBrain(this);
    btNodeTypesModel *nodeTypes = new btNodeTypesModel(brain, this);
    connect(brain, SIGNAL(nodeTypeAdded(btNodeType*)), nodeTypes, SLOT(newBehaviorTreeTypeAdded(btNodeType*)));
    this->availableNodes->setModel(nodeTypes);
    brain->newBehaviorTree();
}

bteditor::~bteditor()
{}

void bteditor::setupActions()
{
    connect(actionQuit, SIGNAL(triggered(bool)), qApp, SLOT(quit()));
}

#include "bteditor.moc"
