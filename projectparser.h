#ifndef _PROJECTPARSER_H_
#define _PROJECTPARSER_H_

#include <QObject>
#include <QtXml>
#include <QtDebug>

#include "btbrain.h"
#include "btcompositenode.h"
#include "nodetypefactory.h"
#include "btnodetype.h"

class projectParser : public QObject
{
	Q_OBJECT
	
public:	
	static projectParser * instance();
	
	//parsing the xmldata, which is a QString which is contents of the xml file
	btBrain* parseProject(QString xmlData);
	//returning the btBrain serialized to a xml formatted QString
	QString serializeProject(btBrain * brain) const;
	
private:
	projectParser();
	
	void parseNodeTypes(QDomNode xNode, btBrain * brain);
	void parseBehaviorTrees(QDomNode xNode, btBrain * brain);
};

#endif
