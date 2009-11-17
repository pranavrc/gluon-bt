#include "game.h"
#include "gameitem.h"
#include "agent.h"

#include <QDebug>
#include <QPushButton>
#include <QDateTime>

Game::Game()
{

        qsrand(QDateTime::currentDateTime().toTime_t());
    int locations[15][15] =    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                                0,1,1,1,1,1,1,0,1,1,1,1,1,1,0,
                                0,1,0,0,0,0,0,0,0,0,0,0,0,1,0,
                                0,1,0,1,0,1,1,1,1,1,0,1,0,1,0,
                                0,1,0,1,0,0,0,0,0,0,0,1,0,1,0,
                                0,1,0,1,0,1,1,0,1,1,0,1,0,1,0,
                                0,1,0,1,0,1,0,0,0,1,0,1,0,1,0,
                                0,0,0,1,0,1,0,1,0,1,0,1,0,0,0,
                                0,1,0,1,0,1,0,0,0,1,0,1,0,1,0,
                                0,1,0,1,0,1,1,0,1,1,0,1,0,1,0,
                                0,1,0,1,0,0,0,0,0,0,0,1,0,1,0,
                                0,1,0,1,0,1,1,1,1,1,0,1,0,1,0,
                                0,1,0,0,0,0,0,0,0,0,0,0,0,1,0,
                                0,1,1,1,1,1,1,0,1,1,1,1,1,1,0,
                                0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};


    for(int i = 0; i < 15; ++i){
        for(int j = 0;j < 15; ++j){
            if(locations[i][j] == 1){
                board[j][i] = new GameItem(j,i,this);
                board[j][i]->setBrush(Qt::red);
                board[j][i]->setBlocks(true);
            }else{
                board[j][i] = new GameItem(j,i,this);
                board[j][i]->setBlocks(false);
                QPolygonF myPolygon;
                myPolygon << QPointF(-5, 0) << QPointF(0, 5)
                        << QPointF(5, 0) << QPointF(0, -5)
                        << QPointF(-5, 0);
                board[j][i]->setPolygon(myPolygon);
            }
            board[j][i]->occupant = NULL;
            this->addItem(board[j][i]);
        }
    }

    for(int i = 0; i < 16; ++i){
        this->addLine((float)(i * 20),0.0,(float)(i * 20),300.0,QPen(QColor(Qt::gray)));
        this->addLine(0.0,(float)(i * 20),300.0,(float)(i * 20),QPen(QColor(Qt::gray)));
    }
    marker = new GameItem(this);
    marker->setPos(10.0,10.0);
    marker->setBrush(Qt::yellow);
    this->addItem(marker);
    Agent *agent = new Agent(this,QPoint(14,14));
    Agent *agent2 = new Agent(this,QPoint(0,0));
    Agent *agent3 = new Agent(this,QPoint(0,14));
    Agent *agent4 = new Agent(this,QPoint(14,0));
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
