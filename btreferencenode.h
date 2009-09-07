#ifndef _BTREFERENCENODE_H_
#define _BTREFERENCENODE_H_

#include "btNodeType.h"

class btReferenceNode :public btNodeType
{
	Q_OBJECT
	
public:
	btReferenceNode();	
	~btReferenceNode();
};

#endif