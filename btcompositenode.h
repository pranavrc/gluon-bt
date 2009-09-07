#ifndef _BTCOMPOSITNODE_H_
#define _BTCOMPOSITNODE_H_

#include "btNodeType.h"

class btCompositeNode : public btNodeType
{
	Q_OBJECT
	
public:
	btCompositeNode();	
	~btCompositeNode();
};

#endif