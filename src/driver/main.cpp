#include <QtGui/QApplication>
#include "driver.h"
#include "../gluon-bt-lib/btlib.h"
#include <QDebug>
#include <QFile>

int main(int argc, char** argv)
{
    QCoreApplication app(argc, argv);

    QString fileName = "test.xml";

    QFile file(fileName);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        return app.exec();
    }
    QByteArray byteArray = file.readAll();
    QString fileContents(byteArray.data());
    file.close();

   //qDebug()  << fileContents;

    btBrain *brain = new btBrain(fileContents);
    for(int i = 0; i < 1; i++){

    btCharacter *agent1 = new btCharacter();
    agent1->setName("Agent One");
    btCharacter *agent2 = new btCharacter();
    agent2->setName("Agent Two");

    brain->getBehaviorTree(0)->runBehavior(agent1);
    brain->getBehaviorTree(0)->runBehavior(agent2);
    qDebug()  << "------------";
}


    //qDebug() << brain->children();


    return app.exec();
}
