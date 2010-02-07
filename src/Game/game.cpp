#include "game.h"
#include "gameitem.h"
#include "agent.h"
#include "enemy.h"
#include "runner.h"

#include <QDebug>
#include <QPushButton>
#include <QDateTime>
#include <QFile>
#include "scenario.h"
#include "scenarioset.h"
#include "mainwindow.h"
#include "colorgen.h"

Game::Game(MainWindow *ui)
{
    this->ui = ui;
    gameCounter = 0;
    qsrand(QDateTime::currentDateTime().toTime_t());
    int locations[15][15] =    {2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                                0,1,1,1,1,1,1,0,1,1,1,1,1,1,0,
                                0,1,0,0,0,0,0,0,0,0,0,0,0,1,0,
                                0,1,0,1,2,1,1,1,1,1,2,1,0,1,0,
                                0,1,0,1,0,0,0,0,0,0,0,1,0,1,0,
                                0,1,0,1,0,1,1,0,1,1,0,1,0,1,0,
                                0,1,0,1,0,1,0,0,0,1,0,1,0,1,0,
                                0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,
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
                board[j][i]->setPen(QPen(QColor(Qt::transparent)));
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
    QString fileName = "test2.glbt.xml";

    QFile file(fileName);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        qDebug("Could not open behavior tree file");
        return;
    }
    QByteArray byteArray = file.readAll();
    QString fileContents(byteArray.data());
    file.close();

/*    QString logFilename = "log.txt";

    logFile = new QFile(logFilename);
    if(!logFile->open(QIODevice::Append | QIODevice::Text)){
        qDebug("Could not open file");
        return;
    }

    QTextStream out(logFile);
    out << ";Board;Killtime;Avg Killtime;Interest;Challenge;Behavior Div;Spatial Div;Max Deviation;Standard Deviation;\n";//*/


    //QByteArray byteArray = logFile.readAll();
   // QString fileContents(byteArray.data());

    //file.close();

    btBrain *brain = new btBrain(fileContents);
    
    //this->setBackgroundBrush(QBrush(QColor(Qt::black)));

   /* ss = new ScenarioSet();
    Scenario *s1 = new Scenario();

    ss->addScenario(s1);*/
    
    marker = new Player(this,QPoint(8,12));//new GameItem(this);
    connect(marker, SIGNAL(pacmanLost()), this, SLOT(resetAfterLost()));
    connect(marker, SIGNAL(pacmanWon()), this, SLOT(resetAfterWon()));


    marker->setBrush(Qt::magenta);
    
    Enemy *player = new Enemy(marker,brain->getBehaviorTree(2));
    player->thename = "mr. anderson";
    Runner* playerRunner = new Runner(player);
    connect(playerRunner, SIGNAL(finished()), this, SLOT(resetGame()));
    runners.append(playerRunner);//*/
    
    //int trees[3] = {6,7,9}; // pinky
    //int trees[3] = {7,7,9}; // clyde
    //int trees[3] = {9,7,9}; // Blinky
    //int trees[3] = {0,7,9}; // Pure Random*/
	
	//int trees[1] = {0};
	int trees[1] = {1};

    ColorGen colors(0,255,30);

    for (int i = 0; i < this->numberOfEnemies(); i++)
    {
        Guard* agent = new Guard(this,QPoint(0,0));
        Enemy *enemy = new Enemy(agent,brain->getBehaviorTree(trees[i]));
        agent->setBrush(QBrush(colors.nextColor()));
        
        Runner* runner = new Runner(enemy);
        connect(runner, SIGNAL(finished()), this, SLOT(resetGame()));
        runners.append(runner);
        enemy->thename = "mr. smith " + QVariant(i).toString();
        agent->addObjective(marker);
        //connect(agent, SIGNAL(enteredNewCell(int,int)), s1, SLOT(visit(int,int)));
        marker->addObjective(agent);
    }//*/

    foreach(GameItem* goal,goals){
        marker->addGoal(goal);
    }

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

void Game::resetAfterWon()
{
    reset();
}

void Game::resetAfterLost()
{
        reset();
    
   /* QTextStream out(logFile);



    for(int x = 0; x < 15; ++x){
        for(int y = 0;y < 15; ++y){
            out << QString("%1").arg(ss->scenarioList().last()->board[x][y]) << ((x==14&&y==14) ? "" : ":");
        }
    }

    out << ";" << ss->scenarioList().last()->getKillTime();
    out << ";" << ss->calcAverageKillTime();
    out << ";" << ss->calculateInterest();
    out << ";" << ss->calculateChallengeLevel();
    out << ";" << ss->calculateBehavioralDiversity();
    out << ";" << ss->calculateSpatialDiversity();
    out << ";" << ss->calcMaximumDeviation();
    out << ";" << ss->calcStandardDeviation();
    out << "\n";

    Guard *ghost = static_cast<Guard*>(runners.last()->getTarget()->target);

    disconnect(ghost, SIGNAL(enteredNewCell(int,int)), ss->scenarioList().last(), SLOT(visit(int,int)));


    Scenario *s = new Scenario();
    ss->addScenario(s);

    connect(ghost, SIGNAL(enteredNewCell(int,int)), s, SLOT(visit(int,int)));*/

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
            //board[i][j]->setVisible(true);
            if(!board[i][j]->isVisible()){
                board[i][j]->setGoal(true);
                board[i][j]->setVisible(true);
            }

            //board[i][j]->setBrush(brush);
            /*if(board[i][j]->occupant != NULL){
             board[i][j]->occupant->setSquare(qrand() % 14, qrand() % 14);
             }*/
        }
    }

  //  ui->takeScreenshot(gameCounter++);
  //  ui->updateInterest(gameCounter);
    
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
            marker->setSquare(8,12);
            marker->collided = false;
        }
        else 
        {
            t->target->setSquare(0,0);
            t->target->setDirection(GameItem::None);
        }        
    }


    marker->setSquare(8,12);
    marker->collided = false;
    marker->counter = 0;
    marker->score = 0;//*/
    
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
    return 1;
}

#include "game.moc"

