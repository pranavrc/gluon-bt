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

void btChildListWidget::setChildProbabilites(QObject* object, bool enabled)
{
    btEditorNodeType * nodeType = qobject_cast<btEditorNodeType*>(object);
    btNode* node = qobject_cast<btNode*>(nodeType->parentNode());
    
    if(!nodeType->property("probabilities").isValid())
    {
        nodeType->setProperty("probabilities", QVariant::List);
    }
    
    for (int i = 0; i < node->childCount(); i++) 
    {        
        QLabel * nodeName = new QLabel(this);
        nodeName->setText(node->child(i)->name());
        
        QDoubleSpinBox * prob = new QDoubleSpinBox(this);
        prob->setRange(0.0, 1.0);
        prob->setSingleStep(0.01);
        prob->setEnabled(enabled);
        
        QVariantList probList = nodeType->property("probabilities").toList();
        if(i > probList.count()-1)
        {
            probList.append(0.5);
            nodeType->setProperty("probabilities", probList);
            prob->setValue(0.5);
        }
        else
        {
            prob->setValue(probList[i].toDouble());
        }
        
        connect(prob, SIGNAL(valueChanged(double)), node->child(i)->type(), SLOT(changeProbability(double)));
        
        childLayout->addWidget(nodeName);
        childLayout->addWidget(prob);

    }
    this->setLayout(childLayout);
}

#include "btchildlistwidget.moc"