#include "game.h"
#include "gameitem.h"

#include <QDebug>

Game::Game()
{
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
            }
            this->addItem(board[j][i]);
        }
    }

    for(int i = 0; i < 16; ++i){
        this->addLine((float)(i * 20),0.0,(float)(i * 20),300.0,QPen());
        this->addLine(0.0,(float)(i * 20),300.0,(float)(i * 20),QPen());
    }
    marker = new GameItem(this);
    marker->setPos(10.0,10.0);
    marker->setBrush(Qt::cyan);
    this->addItem(marker);
}

void Game::drawItems(){

}
