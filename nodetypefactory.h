#ifndef _NODETYPEFACYORY_H_
#define _NODETYPEFACYORY_H_

#include <QObject>

#include "btnodetype.h"

class nodeTypeFactory: public QObject
{
		Q_OBJECT
	
public:
	static nodeTypeFactory * instance();
	
	btNodeType * newObject(QString typeCategory);
    btNodeType * newObject(btNodeType::nodeType type);
private:
	nodeTypeFactory();
};

#endif
