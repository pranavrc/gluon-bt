#ifndef _BTDECORATORNODE_H_
#define _BTDECORATORNODE_H_

#include "bteditornodetype.h"

class btDecoratorNode : public btEditorNodeType
{
	Q_OBJECT
	
public:
	btDecoratorNode();	
	~btDecoratorNode();
	
	bool run();
    
    const QString toDataXml();
};

#endif
