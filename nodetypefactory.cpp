#include "nodetypefactory.h"

nodeTypeFactory::nodeTypeFactory()
{
}


nodeTypeFactory* nodeTypeFactory::instance()
{
	static nodeTypeFactory * factoryInstance;
	if(factoryInstance == NULL)
	{
		factoryInstance = new nodeTypeFactory();
	}
	
	return factoryInstance;
}

btNodeType * nodeTypeFactory::newObject(QString typeCategory)
{
	btNodeType * newNode = 0;
	
	if(typeCategory == tr("action"))
	{
		newNode = new btActionNode(this);
	}
	else if(typeCategory == tr("condition"))
	{
		newNode = new btConditionNode();		
	}
	else if(typeCategory == tr("composite"))
	{
		newNode = new btCompositeNode();
	}
	else if(typeCategory == tr("decorator"))
	{
		newNode = new btDecoratorNode();
	}
	else if(typeCategory == tr("reference"))
	{
		newNode = new btReferenceNode();
	}
	else
	{
		newNode = new btUnusableNode();
	}
	
	return newNode;
}
	

#include "nodetypefactory.moc"