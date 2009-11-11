#include <QtGui/QApplication>
#include "driver.h"
#include "../gluon-bt-lib/btlib.h"
#include <QDebug>
#include <QFile>

int main(int argc, char** argv)
{
    QCoreApplication app(argc, argv);

    QString fileName = "debug2.xml";

    QFile file(fileName);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        return app.exec();
    }
    QByteArray byteArray = file.readAll();
    QString fileContents(byteArray.data());
    file.close();

   //qDebug()  << fileContents;

    btBrain *brain = new btBrain(fileContents);
    for(int i = 0; i < 10; i++){

    brain->getBehaviorTree(0)->runBehavior();
    qDebug()  << "------------";
}


    //qDebug() << brain->children();


    return app.exec();
}
