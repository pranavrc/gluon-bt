#ifndef GAME_H
#define GAME_H

#include <QGraphicsScene>
#include "player.h"
#include "guard.h"
#include <QDebug>
#include <QKeyEvent>
#include <QTimeLine>
#include "runner.h"

class GameItem;

class Game : public QGraphicsScene
{
    Q_OBJECT
public:
    Game();
    Player* marker;
    Guard* agent;
    Guard* agent2;
    Guard* agent3;
    Guard* agent4;
/*    Runner *runner;
    Runner *playerRunner;*/
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
    
public Q_SLOTS:
    void resetGame();
    void reset();
    
private:
    QList<Runner*> runners;
};

#endif // GAME_H
