#include "btparallelconditionswidget.h"

#include "btglobal.h"
#include "bteditornodetype.h"
#include "btnode.h"

#include <QtCore/QVariant>
#include <QtGui/QLabel>
#include <QtGui/QVBoxLayout>
#include <QtGui/QCheckBox>

btParallelConditionsWidget::btParallelConditionsWidget(QWidget * parent) : QWidget(parent)
{
	parallelConditionsLayout = new QVBoxLayout(this);
}

btParallelConditionsWidget::~btParallelConditionsWidget()
{
	qDeleteAll(parallelConditionsLayout->children());
	delete parallelConditionsLayout;
}

void btParallelConditionsWidget::setParallelConditions(QString propertyName, QObject* object, bool enabled)
{
	qRegisterMetaType<btParallelConditions>("btParallelConditions");
    
    btEditorNodeType * nodeType = qobject_cast<btEditorNodeType*>(object);
    btNode* node = qobject_cast<btNode*>(nodeType->parentNode());
    
    if(!nodeType->property(propertyName.toUtf8()).isValid())
    {
        btParallelConditions pc;
        QVariant v;
        v.setValue(pc);
        nodeType->setProperty(propertyName.toUtf8(), v);
    }
	
	btParallelConditions conditionsList = nodeType->property(propertyName.toUtf8()).value<btParallelConditions>();
    for (int i = 0; i < node->childCount(); i++) 
    {        
        QLabel * nodeName = new QLabel(this);
        nodeName->setText(node->child(i)->name());
        
		QCheckBox * sCheckBox = new QCheckBox(this);
		sCheckBox->setEnabled(enabled);
		sCheckBox->setText("Succeeded");
		QCheckBox * fCheckBox = new QCheckBox(this);
		fCheckBox->setEnabled(enabled);
		fCheckBox->setText("Failed");
		
        
        if(i > conditionsList.parallelConditions.count()-1)
        {
            conditionsList.parallelConditions.append(1.0);
            sCheckBox->setCheckState(Qt::Checked);
        }
        else
        {
			double value = conditionsList.parallelConditions[i].toDouble();
			
			if(value >= 1.0)
			{
				sCheckBox->setCheckState(Qt::Checked);
				fCheckBox->setCheckState(Qt::Unchecked);
			}
			else if (value <= 0.0)
			{
				sCheckBox->setCheckState(Qt::Unchecked);
				fCheckBox->setCheckState(Qt::Checked);
			}
        }
        
        connect(sCheckBox, SIGNAL(stateChanged(int)), node->child(i)->type(), SLOT(changeCondition(int)));
		connect(fCheckBox, SIGNAL(stateChanged(int)), node->child(i)->type(), SLOT(changeCondition(int)));
        
        parallelConditionsLayout->addWidget(nodeName);
        parallelConditionsLayout->addWidget(sCheckBox);
		parallelConditionsLayout->addWidget(fCheckBox);
		
    }
    QVariant v;
    v.setValue(conditionsList);
    nodeType->setProperty(propertyName.toUtf8(), v);
    this->setLayout(parallelConditionsLayout);
}

#include "btparallelconditionswidget.moc"
