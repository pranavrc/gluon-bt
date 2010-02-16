#ifndef BTREFERENCENODE_H
#define BTREFERENCENODE_H

#include "btnode.h"

#include <QtCore/QObject>

class btCharacter;

class BT_LIB_EXPORT btReferenceNode : public btNode 
{
	Q_OBJECT
public:
	Q_INVOKABLE btReferenceNode();
	~btReferenceNode();
	
	btNode::status run(btCharacter * self);
	
	void addParentNode(btNode* parent);
	btNode* getParentNode();
	
private:
	
};

#endif