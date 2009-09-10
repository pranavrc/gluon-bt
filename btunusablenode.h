#ifndef _BTUNUSABLENODE_H_
#define _BTUNUSABLENODE_H_

#include "btnodetype.h"

class btUnusableNode : public btNodeType
{
	Q_OBJECT
		
public:
	btUnusableNode();	
	~btUnusableNode();
	
	bool run();
};

#endif