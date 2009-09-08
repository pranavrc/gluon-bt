#ifndef _BTCOMPOSITNODE_H_
#define _BTCOMPOSITNODE_H_

#include "btnodetype.h"

class btCompositeNode : public btNodeType
{
	Q_OBJECT
	
public:
	btCompositeNode();	
	~btCompositeNode();
};

#endif