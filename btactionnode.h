#ifndef _BTACTIONNODE_H_
#define _BTACTIONNODE_H_

#include "btnodetype.h"

class btActionNode : public btNodeType
{
	Q_OBJECT
	
public:
	btActionNode(QObject* parent = 0);	
	~btActionNode();
	
	bool run();
};

#endif