#include <QtGui/QApplication>
#include "btnodetype.h"
#include "btnodetypefactory.h"


int main(int argc, char** argv)
{
    QApplication app(argc, argv);
    btNodeType* node = btNodeTypeFactory::instance()->newObject("Selector");
    return app.exec();
}
