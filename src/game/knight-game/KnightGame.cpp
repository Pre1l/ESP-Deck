#include "game/knight-game/KnightGame.hpp"

KnightGame* KnightGame::instance = nullptr;

KnightGame::KnightGame() 
{
    Vector2D startPosition(0, 0);
    knight = new Knight(startPosition);
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
    Serial.println(knight->getPosition().getY());
    Serial.println(knight->getHitbox().getPosition().getY());
    knight->update(deltaTime);
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