#ifndef _BTDECORATORNODE_H_
#define _BTDECORATORNODE_H_

#include "btnodetype.h"

class btDecoratorNode : public btNodeType
{
	Q_OBJECT
	
public:
	btDecoratorNode();	
	~btDecoratorNode();
	
	bool run();
};

#endif