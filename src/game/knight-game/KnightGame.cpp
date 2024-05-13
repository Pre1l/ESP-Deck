#include "game/knight-game/KnightGame.hpp"

KnightGame* KnightGame::instance = nullptr;

KnightGame::KnightGame() 
{
    
}

KnightGame* KnightGame::getInstance() 
{
    if (instance == nullptr) {
        instance = new KnightGame();
    }

    return instance;
}

void KnightGame::update(float deltatTime) 
{

}

void KnightGame::keyPressed(int key)
{

}

void KnightGame::keyReleased(int key)
{

}

void KnightGame::onGameClosed() 
{

}