#include "game.h"
#include "gameitem.h"
#include "agent.h"
#include "enemy.h"
#include "runner.h"

#include <QDebug>
#include <QPushButton>
#include <QDateTime>
#include <QFile>

Game::Game()
{

    qsrand(QDateTime::currentDateTime().toTime_t());
    int locations[15][15] =    {2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                                0,1,1,1,1,1,1,0,1,1,1,1,1,1,0,
                                0,1,0,0,0,0,0,0,0,0,0,0,0,1,0,
                                0,1,0,1,2,1,1,1,1,1,2,1,0,1,0,
                                0,1,0,1,0,0,0,0,0,0,0,1,0,1,0,
                                0,1,0,1,0,1,1,0,1,1,0,1,0,1,0,
                                0,1,0,1,0,1,0,0,0,1,0,1,0,1,0,
                                0,0,0,1,0,1,0,1,0,1,0,1,0,0,0,
                                0,1,0,1,0,1,0,0,0,1,0,1,0,1,0,
                                0,1,0,1,0,1,1,0,1,1,0,1,0,1,0,
                                0,1,0,1,0,0,0,0,0,0,0,1,0,1,0,
                                0,1,0,1,2,1,1,1,1,1,2,1,0,1,0,
                                0,1,0,0,0,0,0,0,0,0,0,0,0,1,0,
                                0,1,1,1,1,1,1,0,1,1,1,1,1,1,0,
                                2,0,0,0,0,0,0,0,0,0,0,0,0,0,2};

    for(int i = 0; i < 15; ++i){
        for(int j = 0;j < 15; ++j){
            if(locations[i][j] == 1){
                board[j][i] = new GameItem(j,i,this);
                board[j][i]->setGoal(false);
                board[j][i]->setBrush(Qt::red);
                board[j][i]->setBlocks(true);
                board[j][i]->setZValue(8);
            }else if(locations[i][j] == 0){
                board[j][i] = new GameItem(j,i,this);
                board[j][i]->setBlocks(false);
                board[j][i]->setGoal(false);
                QPolygonF myPolygon;
                myPolygon << QPointF(-5, 0) << QPointF(0, 5)
                        << QPointF(5, 0) << QPointF(0, -5)
                        << QPointF(-5, 0);
                board[j][i]->setPolygon(myPolygon);
                board[j][i]->setZValue(0);
                board[j][i]->setBrush(Qt::white);
            }else if(locations[i][j] == 2){
                board[j][i] = new GameItem(j,i,this);
                board[j][i]->setBlocks(false);
                board[j][i]->setGoal(true);
                QPolygonF myPolygon;
                myPolygon << QPointF(-5, 0) << QPointF(0, 5)
                        << QPointF(5, 0) << QPointF(0, -5)
                        << QPointF(-5, 0);
                board[j][i]->setPolygon(myPolygon);
                board[j][i]->setZValue(0);
                board[j][i]->setBrush(Qt::blue);
                goals.append(board[j][i]);
            }
            board[j][i]->occupant = NULL;
            this->addItem(board[j][i]);
        }
    }

    /*for(int i = 0; i < 16; ++i){
        this->addLine((float)(i * 20),0.0,(float)(i * 20),300.0,QPen(QColor(Qt::gray)));
        this->addLine(0.0,(float)(i * 20),300.0,(float)(i * 20),QPen(QColor(Qt::gray)));
    }*/
    marker = new Player(this,QPoint(0,14));//new GameItem(this);
    //marker->setPos(10.0,10.0);
    marker->setBrush(Qt::yellow);
    marker->setZValue(10);
    this->addItem(marker);

    // --------------------------------------
    QString fileName = "test.glbt.xml";

    QFile file(fileName);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        return;
    }
    QByteArray byteArray = file.readAll();
    QString fileContents(byteArray.data());
    file.close();

    btBrain *brain = new btBrain(fileContents);
    agent = new Guard(this,QPoint(14,0));
    //agent2 = new Guard(this,QPoint(0,0));
   // agent3 = new Guard(this,QPoint(14,14));
  //  agent4 = new Guard(this,QPoint(0,14));

    Enemy *player = new Enemy(marker,brain->getBehaviorTree(2));

    Enemy *enemy = new Enemy(agent,brain->getBehaviorTree(3));
  //  Enemy *enemy2 = new Enemy(agent2,brain->getBehaviorTree(3));
  //  Enemy *enemy3 = new Enemy(agent3,brain->getBehaviorTree(3));
  //  Enemy *enemy4 = new Enemy(agent4,brain->getBehaviorTree(3));

    this->setBackgroundBrush(QBrush(QColor(Qt::black)));

    Runner *runner = new Runner(enemy);
    runner->start();
    //Runner *runner2 = new Runner(enemy2);
    //runner2->start();
    //Runner *runner3 = new Runner(enemy3);
    //runner3->start();
    //Runner *runner4 = new Runner(enemy4);
    //runner4->start();
}


void Game::reset()
{
    for(int i = 0; i < 15; ++i){
        for(int j = 0;j < 15; ++j){
            board[i][j]->setVisible(true);
            if(board[i][j]->occupant != NULL){
                board[i][j]->occupant->setSquare(0,0);
            }
        }
    }
}

void Game::drawItems(){

}
