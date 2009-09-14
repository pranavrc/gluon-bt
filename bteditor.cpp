#include <QMessageBox>
#include <QFileDialog>
#include <QFile>

#include "bteditor.h"
#include "btbrain.h"
#include "bttreemodel.h"
#include "btnodetypesmodel.h"
#include "btnode.h"
#include "modeltest.h"
#include "treeselectordialog.h"
#include "projectparser.h"

bteditor::bteditor(QWidget *parent)
{
    setupUi(this);
    setupActions();
	
//////////
	//remove this and use the menu items for loading :D
	QFile file("xmlData.xml");
        file.open(QIODevice::ReadOnly | QIODevice::Text);
	QByteArray byteArray = file.readAll();
	QString fileContents(byteArray.data());	
	file.close();
///////////
	
    m_brain = projectParser::instance()->parseProject(fileContents); //new btBrain(this);
    btNodeTypesModel *nodeTypes = new btNodeTypesModel(m_brain, this);
    treeSelectDialog = new TreeSelectorDialog();
    connect(
        m_brain, SIGNAL(nodeTypeAdded(btNodeType*)),
        nodeTypes, SLOT(newBehaviorTreeTypeAdded(btNodeType*))
        );
    connect(
        m_brain, SIGNAL(behaviorTreeAdded(btTreeModel*)),
        this, SLOT(newBehaviorTreeAdded(btTreeModel*))
        );
    this->availableNodes->setModel(nodeTypes);
//    m_brain->newBehaviorTree();
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
}

void bteditor::showBehaviorTree(btTreeModel* showThis)
{
    disconnect(this, SLOT(editorSelectionChanged(QItemSelection,QItemSelection)));
    this->btEditor->setModel(showThis);
    this->btEditor->setSelectionModel(new QItemSelectionModel(showThis));
    connect(
        this->btEditor->selectionModel(), SIGNAL(selectionChanged(QItemSelection,QItemSelection)),
        this, SLOT(editorSelectionChanged(QItemSelection,QItemSelection))
        );
    this->currentBTNameLabel->setText(showThis->name());
    //new ModelTest(showThis, this);
}

void bteditor::editorSelectionChanged(const QItemSelection& selected, const QItemSelection& deselected)
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
    treeSelectDialog->updateModel(m_brain->behaviorTrees);
    treeSelectDialog->show();
    //QMessageBox::about(this, this->windowTitle(), "Show list of all behavior trees... menu permayhaps?");
}

void bteditor::newBehaviorTreeAdded(btTreeModel* newTree)
{
    showBehaviorTree(newTree);
    treeSelectDialog->updateModel(newTree);
}

#include "bteditor.moc"

void bteditor::on_actionOpen_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),
                                                 "",
                                                 tr("Behavior Trees (*.glbt *.xml)"));
    QMessageBox::about(this, this->windowTitle(),fileName);
}

void bteditor::on_actionSave_As_triggered()
{
    // get name of tree, use when saving
     QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"),
                            "untitled.glbt",
                            tr("Behavior Trees (*.glbt *.xml)"));
     // call kims code
}
