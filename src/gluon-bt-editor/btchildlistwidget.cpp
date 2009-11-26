#include "btchildlistwidget.h"

#include <QLabel>
#include <QDoubleSpinBox>
#include <QVariant>

#include "btnode.h"
#include "bteditornodetype.h"

btChildListWidget::btChildListWidget(QWidget * parent) : QWidget(parent)
{
    childLayout = new QVBoxLayout(this);
}

btChildListWidget::~btChildListWidget()
{
}

void btChildListWidget::setChildProbabilites(QObject* object, bool readOnly)
{
    btEditorNodeType * nodeType = qobject_cast<btEditorNodeType*>(object);
    btNode* node = qobject_cast<btNode*>(nodeType->parentNode());
    
    for (int i = 0; i < node->childCount(); i++) 
    {        
        QLabel * nodeName = new QLabel(this);
        nodeName->setText(node->child(i)->name());
        
        QDoubleSpinBox * prob = new QDoubleSpinBox(this);
        prob->setRange(0.0, 1.0);
        prob->setSingleStep(0.01);
        prob->setReadOnly(readOnly);
        
        if(!node->child(i)->type()->property("probability").isValid())
        {
            node->child(i)->type()->setProperty("probability", 0.0);
        }
        
        prob->setValue(node->child(i)->type()->property("probability").toDouble());
        
        btEditorNodeType* editorNodeType = qobject_cast<btEditorNodeType*>(node->child(i)->type());
        
        connect(prob, SIGNAL(valueChanged(double)), editorNodeType, SLOT(changeProbability(double)));
        
        childLayout->addWidget(nodeName);
        childLayout->addWidget(prob);

    }
    this->setLayout(childLayout);
}

#include "btchildlistwidget.moc"
