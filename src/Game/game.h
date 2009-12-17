#ifndef GAME_H
#define GAME_H

#include <QGraphicsScene>
#include "player.h"
#include "guard.h"
#include <QDebug>
#include <QKeyEvent>
#include <QTimeLine>
#include "runner.h"
#include "mainwindow.h"
#include <QFile>


class GameItem;
class ScenarioSet;

class Game : public QGraphicsScene
{
    Q_OBJECT
public:
    Game(MainWindow *ui);
    Player* marker;
    //Guard* agent;
    ScenarioSet *ss;
    QFile *logFile;
    /*Guard* agent2;
    Guard* agent3;
    Guard* agent4;
/*    Runner *runner;
    Runner *playerRunner;*/
    int gameCounter;
    void drawItems();
    GameItem* board[16][16];
    QList<GameItem*> goals;
    void keyPressEvent(QKeyEvent *event){
       qDebug() << event->key();
       switch(event->key()){
           case Qt::Key_W:
                marker->goUp();
                break;
           case Qt::Key_S:
                marker->goDown();
                break;
           case Qt::Key_A:
                marker->goLeft();
                break;
           case Qt::Key_D:
                marker->goRight();
                break;
           case Qt::Key_Return:
                marker->timer->start();
                break;
           default:
                break;
       }

        QGraphicsScene::keyPressEvent(event);
    }
    
    int numberOfEnemies();
    
public Q_SLOTS:
    void resetAfterWon();
    void resetAfterLost();
    void resetGame();
    void reset();
    
private:
    MainWindow *ui;
    QList<Runner*> runners;

};

#endif // GAME_H
