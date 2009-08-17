#include <QtGui/QApplication>
#include "bteditor.h"


int main(int argc, char** argv)
{
    QApplication app(argc, argv);
    bteditor foo;
    foo.show();
    return app.exec();
}
