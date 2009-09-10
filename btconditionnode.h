#ifndef _BTCONDITIONNODE_H_
#define _BTCONDITIONNODE_H_

#include "btnodetype.h"

class btConditionNode : public btNodeType
{
	Q_OBJECT
		
public:
	btConditionNode();	
	~btConditionNode();
	
	bool run();
};

#endif