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
                board[j][i]->setZValue(0);
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
    
    this->setBackgroundBrush(QBrush(QColor(Qt::black)));
    
    marker = new Player(this,QPoint(0,0));//new GameItem(this);
    connect(marker, SIGNAL(pacmanLost()), this, SLOT(reset()));
    connect(marker, SIGNAL(pacmanWon()), this, SLOT(reset()));
    marker->setBrush(Qt::yellow);
    
    Enemy *player = new Enemy(marker,brain->getBehaviorTree(4));
    player->thename = "mr. anderson";
    Runner* playerRunner = new Runner(player);
    connect(playerRunner, SIGNAL(finished()), this, SLOT(resetGame()));
    runners.append(playerRunner);
    
    for (int i = 0; i < this->numberOfEnemies(); i++)
    {
        Guard* agent = new Guard(this,QPoint(14,i));        
        Enemy *enemy = new Enemy(agent,brain->getBehaviorTree(3));
        
        Runner* runner = new Runner(enemy);
        connect(runner, SIGNAL(finished()), this, SLOT(resetGame()));
        runners.append(runner);
        enemy->thename = "mr. smith " + QVariant(i).toString();
        agent->addObjective(marker);
        marker->addObjective(agent);
    }//*/

    foreach(Runner* r , runners)
    {
        r->start();
    }
    
    //Runner *runner2 = new Runner(enemy2);
    //runner2->start();
    //Runner *runner3 = new Runner(enemy3);
    //runner3->start();
    //Runner *runner4 = new Runner(enemy4);
    //runner4->start();
}


void Game::reset()
{    
    foreach(Runner* r , runners)
    {
        r->getTarget()->stopThinking();
    }
}

void Game::resetGame()
{
    foreach(Runner* r , runners)
    {
        if(r->isRunning())
        {
            return;
        }
    }
    
    

    //qDebug() << "resetting";
    QBrush brush(QColor(Qt::white));

    for(int i = 0; i < 15; ++i){
        for(int j = 0;j < 15; ++j){
            board[i][j]->setVisible(true);

            //board[i][j]->setBrush(brush);
            /*if(board[i][j]->occupant != NULL){
             board[i][j]->occupant->setSquare(qrand() % 14, qrand() % 14);
             }*/
        }
    }
    
    for(int i = 0; i <runners.count(); i++)
    {
        Enemy* t = runners[i]->getTarget();
        
        delete runners[i];
        runners[i] = new Runner(t);
        connect(runners[i], SIGNAL(finished()), this, SLOT(resetGame()));
        t->startThinking();
        t->target->collided = false;
        
        if(t->target == marker)
        {
            marker->setSquare(0,0);
        }
        else 
        {
            t->target->setSquare(14,14);
            t->target->setDirection(GameItem::None);
        }        
    }
    
    foreach(Runner* r , runners)
    {
        r->start();
    }
    
//    marker->collided = false;
  //  agent->collided = false;
  //  runner->start();
  //  playerRunner->start();
}

void Game::drawItems(){

}

int Game::numberOfEnemies()
{
    return 2;
}

#include "game.moc"
