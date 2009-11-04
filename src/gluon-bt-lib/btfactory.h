#ifndef BTFACTORY_H
#define BTFACTORY_H

#include <QObject>
#include <QHash>
#include <QDomNode>

class btNodeType;
class btNode;
class btBrain;

class btFactory : public QObject
{
    Q_OBJECT
    
public:
    static btFactory* instance();
    
    btNode* newObject(QString className);
    btNode* newObject(QDomNode xmlNode, btNode* parentNode, btBrain* brain);
    
    btNode* createRootNode(QDomNode xmlNode, btBrain* brain);
    
    void addProperty(btNode* node, QDomNode xNode, btBrain* brain);
    void initNodeType(QDomNode xmlNode);
    
    btNodeType* getRegisteredNodeType(QString className);
    
    void registerNodeType(btNodeType* newType);
    
private:    
    btFactory();
    
    QHash<QString, btNodeType*> m_nodeTypes;
};

template<class T>
class Registration
{

public:
    Registration(T* newNodeType)
    {
        btFactory::instance()->registerNodeType(newNodeType);
    }
};

#define REGISTER_NODETYPE(NEWNODETYPE) \
Registration<NEWNODETYPE> NEWNODETYPE ## _registration_(new NEWNODETYPE());

#endif // BTABSTRACTFACTORY_H
