#ifndef _NODETYPEFACYORY_H_
#define _NODETYPEFACYORY_H_

#include <QObject>
#include "btnodetype.h"
#include "btactionnode.h"
#include "btcompositenode.h"
#include "btconditionnode.h"
#include "btdecoratornode.h"
#include "btreferencenode.h"
#include "btunusablenode.h"

class nodeTypeFactory: public QObject
{
		Q_OBJECT
	
public:
	static nodeTypeFactory * instance();
	
	btNodeType * newObject(QString typeCategory);
private:
	nodeTypeFactory();
};

#endif
