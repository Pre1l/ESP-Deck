#include "game/knight-game/KnightGame.hpp"

KnightGame* KnightGame::instance = nullptr;

KnightGame::KnightGame() 
{
    Vector2D startPosition(0, 0);
    this->knight = new Knight(startPosition);
}

KnightGame* KnightGame::getInstance() 
{
    if (instance == nullptr) {
        instance = new KnightGame();
    }

    return instance;
}

void KnightGame::update(float deltaTime) 
{
    knight->update(deltaTime);
    delay(1);
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