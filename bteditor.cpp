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
#include "btpropertywidget.h"
#include "btnodeeditwidget.h"
#include "btnodemodel.h"

bteditor::bteditor(QWidget *parent)
{
    setupUi(this);
    propertyWidget = new btPropertyWidget(this);
    propertyScrollArea->setWidget(propertyWidget);
    setupActions();
	
    m_brain = new btBrain(this);
    nodeTypes = new btNodeTypesModel(m_brain, this);

    replaceBrain();

    treeSelectDialog = new TreeSelectorDialog(this);

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
    delete propertyWidget;
    propertyWidget = new btPropertyWidget(this);
    propertyScrollArea->setWidget(propertyWidget);
    propertyWidget->setNode(showFor);
}

void bteditor::createNewBehaviorTree()
{
    m_brain->newBehaviorTree();
}

void bteditor::showBehaviorTreeListCicked()
{
    treeSelectDialog->updateModel(m_brain->behaviorTrees);
    treeSelectDialog->show();
}

void bteditor::newBehaviorTreeAdded(btTreeModel* newTree)
{
    showBehaviorTree(newTree);
    treeSelectDialog->updateModel(newTree);
}



void bteditor::on_actionOpen_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),
                                                 "",
                                                 tr("Behavior Trees (*.glbt *.xml)"));
    QFile file(fileName);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QByteArray byteArray = file.readAll();
    QString fileContents(byteArray.data());
    file.close();

    delete m_brain;
    delete nodeTypes;

    m_brain = projectParser::instance()->parseProject(fileContents);
    m_brain->setParent(this);
    nodeTypes = new btNodeTypesModel(m_brain, this);
    replaceBrain();
    showBehaviorTree(m_brain->behaviorTrees[0]);

}

void bteditor::on_actionSave_As_triggered()
{
    // get name of tree, use when saving
     QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"),
                            "untitled.glbt",
                            tr("Behavior Trees (*.glbt *.xml)"));
     QString fileContents = projectParser::instance()->serializeProject(this->m_brain);
}

void bteditor::setBehaviorTree(int index)
{
    // missing sanity check
    showBehaviorTree(m_brain->behaviorTrees[index]);
}

void bteditor::replaceBrain(){
    connect(
        m_brain, SIGNAL(nodeTypeAdded(btNodeType*)),
        nodeTypes, SLOT(newBehaviorTreeTypeAdded(btNodeType*))
        );
    connect(
        m_brain, SIGNAL(behaviorTreeAdded(btTreeModel*)),
        this, SLOT(newBehaviorTreeAdded(btTreeModel*))
        );
    this->availableNodes->setModel(nodeTypes);
}



void bteditor::on_actionEdit_Node_triggered()
{
    //just for testing
    btnodemodel* btm = new btnodemodel(m_brain->nodeTypes,this);
    btNodeEditWidget* editWidget = new btNodeEditWidget();
    editWidget->setModel(btm);
    editWidget->show();
}

#include "bteditor.moc"
