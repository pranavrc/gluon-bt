#ifndef _BTACTIONNODE_H_
#define _BTACTIONNODE_H_

#include "btNodeType.h";

class btActionNode : public btNodeType
{
	Q_OBJECT
	
public:
	btActionNode(QObject* parent = 0);	
	~btActionNode();
};

#endif
