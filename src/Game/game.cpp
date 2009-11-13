#include "game.h"
#include "gameitem.h"

Game::Game()
{
    for(int i = 0; i < 16; i++){
        this->addLine((float)(i * 20),0.0,(float)(i * 20),300.0,QPen());
        this->addLine(0.0,(float)(i * 20),300.0,(float)(i * 20),QPen());
    }
    marker = new GameItem();
    marker->setPos(10.0,10.0);
    this->addItem(marker);
}

Game::drawItems(){
    marker = new GameItem();
    marker->setPos(10.0,10.0);
    this->addItem(marker);
}
