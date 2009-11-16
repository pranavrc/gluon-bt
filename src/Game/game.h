#ifndef GAME_H
#define GAME_H

#include <QGraphicsScene>
#include "gameitem.h"
#include <QDebug>
#include <QKeyEvent>
#include <QTimeLine>

class Game : public QGraphicsScene
{
public:
    Game();
    GameItem *marker;
    void drawItems();
    GameItem* board[16][16];
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
private:

};

#endif // GAME_H
