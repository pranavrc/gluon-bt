#include <QtGui/QApplication>
#include "driver.h"
#include "../gluon-bt-lib/btlib.h"
#include "btprobabilisticselectornode.h"
#include <QDebug>
#include <QFile>

int main(int argc, char** argv)
{
    QCoreApplication app(argc, argv);

    btSelectorNode *sel = new btSelectorNode();
    sel->setClassName("sel");
    qDebug() << sel->className();

    btProbSelectorNode *probSel = new btProbSelectorNode();
    probSel->setClassName("probSel");
    qDebug() << probSel->className();

    QString fileName = "stuff.xml";

    QFile file(fileName);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        return app.exec();
    }
    QByteArray byteArray = file.readAll();
    QString fileContents(byteArray.data());
    file.close();

   qDebug()  << fileContents;

    btBrain *brain = new btBrain(fileContents);

    //qDebug() << brain->children();



    return app.exec();
}
