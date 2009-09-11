#include "btnodetypefactory.h"

btNodeType* btNodeTypeFactory::newObject(QString classname) {
    btNodeType* node = 0;
    if(classname == "Selector"){
        node = new btSelectorNode();
        return node;
    }
}

#include "btnodetypefactory.moc"
