#include "btnodetypefactory.h"

btNodeType* btNodeTypeFactory::newObject(QString classname) {
    btNodeType* node = 0;
    if(classname == "Selector"){
        node = new btSelectorNode();
        return node;
    }
}

btNodeTypeFactory* btNodeTypeFactory::instance() {
    static btNodeTypeFactory* singleton = 0;
    if(singleton == 0){
        singleton = new btNodeTypeFactory();
        //singleton->setParent(qApp); fix
    }
    return singleton;
}

#include "btnodetypefactory.moc"
