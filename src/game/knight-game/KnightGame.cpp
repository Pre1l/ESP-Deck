#include "game/knight-game/KnightGame.hpp"

KnightGame* KnightGame::instance = nullptr;

KnightGame::KnightGame() 
{
    knight = new Knight(Vector2D(0, 0));
    terrains.push_back(Terrain(new Vector2D(0, 300), 480, 20, TFT_WHITE));
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
}

void KnightGame::keyPressed(int key)
{
    Vector2D& velocity = knight->getVelocity();

    switch (key) {
        case 0:
            velocity.addX(0.5);
            break;
        case 1:
            velocity.addY(-0.5);
            break;
        case 2:
            velocity.addX(-0.5);
            break;
        case 3:
            velocity.addY(0.5);
            break;
    }
}

void KnightGame::keyReleased(int key)
{
    Vector2D& velocity = knight->getVelocity();

    switch (key) {
        case 0:
            velocity.addX(-0.5);
            break;
        case 1:
            velocity.addY(0.5);
            break;
        case 2:
            velocity.addX(0.5);
            break;
        case 3:
            velocity.addY(-0.5);
            break;
    }
}

bool KnightGame::calculateCollisions(Rectangle& rectangle) 
{
    for (Rectangle& terrain : terrains) {
        if (rectangle.getId() != terrain.getId() && rectangle.intersects(terrain)) {
            return true;
        }
    }

    Rectangle& knightHitbox = knight->getHitbox();

    if (rectangle.getId() != knightHitbox.getId() && rectangle.intersects(knightHitbox)) {
        return true;
    }

    return false;
}

void KnightGame::onGameClosed() 
{

}