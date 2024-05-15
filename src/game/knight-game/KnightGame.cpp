#include "game/knight-game/KnightGame.hpp"

KnightGame* KnightGame::instance = nullptr;

KnightGame::KnightGame() 
{
    knight = new Knight(Vector2D(133, 0));
    terrains.push_back(Terrain(new Vector2D(0, 300), 480, 20, TFT_WHITE));
    terrains.push_back(Terrain(new Vector2D(0, 0), 20, 300, TFT_WHITE));
    terrains.push_back(Terrain(new Vector2D(460, 0), 20, 300, TFT_WHITE));
    terrains.push_back(Terrain(new Vector2D(150, 270), 40, 30, TFT_WHITE));
    terrains.push_back(Terrain(new Vector2D(100, 270), 40, 30, TFT_WHITE));
    terrains.push_back(Terrain(new Vector2D(20, 100), 100, 20, TFT_WHITE));
    terrains.push_back(Terrain(new Vector2D(190, 210), 40, 30, TFT_WHITE));
    terrains.push_back(Terrain(new Vector2D(230, 150), 40, 30, TFT_WHITE));
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
    Knight* knight = getKnight();

    switch (key) {
        case 0:
            knight->runRight();
            break;
        case 1:
            knight->jump();
            break;
        case 2:
            knight->runLeft();
            break;
    }
}

void KnightGame::keyReleased(int key)
{
    Vector2D& velocity = knight->getVelocity();
    Knight* knight = getKnight();

    switch (key) {
        case 0:
            knight->stopRunRight();
            break;
        case 2:
            knight->stopRunLeft();
            break;
    }
}

float KnightGame::calculateCollision(Rectangle& rectangle, int direction) 
{
    for (Rectangle& terrain : getTerrains()) {
        if (rectangle.getId() != terrain.getId()) {
            float overlap = rectangle.calculateCollision(terrain, direction);

            if (overlap != 0) {
                return overlap;
            }
        }
    }

    Rectangle& knightHitbox = getKnight()->getHitbox();

    if (rectangle.getId() != knightHitbox.getId()) {
        float overlap = rectangle.calculateCollision(knightHitbox, direction);

        if (overlap != 0) {
            return overlap;
        }
    }

    return 0;
}

void KnightGame::onGameClosed() 
{

}

Knight* KnightGame::getKnight() 
{
    return knight;
} 

std::vector<Terrain>& KnightGame::getTerrains() 
{
    return terrains;
}