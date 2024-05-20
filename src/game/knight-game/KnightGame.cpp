#include "game/knight-game/KnightGame.hpp"

KnightGame* KnightGame::instance = nullptr;

KnightGame::KnightGame() 
{
    knight = new Knight(Vector2D(214, 0));

    terrains.push_back(Terrain(new Vector2D(-500, 300), 1320, 20, 0, TFT_WHITE));

    terrains.push_back(Terrain(new Vector2D(200, 240), 40, 20, 0, TFT_WHITE));
    terrains.push_back(Terrain(new Vector2D(300, 200), 160, 20, 0, TFT_WHITE));

    terrains.push_back(Terrain(new Vector2D(100, 80), 40, 20, 0, TFT_WHITE));
    terrains.push_back(Terrain(new Vector2D(170, 140), 40, 20, 0, TFT_WHITE));
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

    float knightX = -(knight->getPosition().getX() - 214);
    for (Terrain& terrain : getTerrains()) {
        terrain.render(knightX);
    }
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
        case 4:
            knight->attack();
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

float KnightGame::calculateCollision(Rectangle& rectangle, int direction, bool returnOverlap) 
{
    for (Rectangle& terrain : getTerrains()) {
        if (rectangle.getId() != terrain.getId()) {
            float overlap = rectangle.calculateCollision(terrain, direction, returnOverlap);

            if (overlap != 0) {
                return overlap;
            }
        }
    }

    Rectangle& knightHitbox = getKnight()->getHitbox();

    if (rectangle.getId() != knightHitbox.getId()) {
        float overlap = rectangle.calculateCollision(knightHitbox, direction, returnOverlap);

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