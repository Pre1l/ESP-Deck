#include "game/knight-game/KnightGame.hpp"

std::shared_ptr<KnightGame> KnightGame::instance = nullptr;

KnightGame::KnightGame() 
{
    setKnight(std::make_shared<Knight>(std::make_shared<Vector2D>(214, 0)));
    terrains.push_back(Terrain(std::make_shared<Vector2D>(-500, 300), 1320, 20, 0, TFT_WHITE));

    terrains.push_back(Terrain(std::make_shared<Vector2D>(200, 240), 40, 20, 0, TFT_WHITE));
    terrains.push_back(Terrain(std::make_shared<Vector2D>(300, 200), 160, 20, 0, TFT_WHITE));

    terrains.push_back(Terrain(std::make_shared<Vector2D>(100, 80), 40, 20, 0, TFT_WHITE));
    terrains.push_back(Terrain(std::make_shared<Vector2D>(170, 140), 40, 20, 0, TFT_WHITE));
}

std::shared_ptr<KnightGame> KnightGame::getInstance() 
{
    if (instance == nullptr) {
        instance = std::shared_ptr<KnightGame>(new KnightGame());
    }

    return instance;
}

void KnightGame::update(float deltaTime) 
{
    TFT_eSPI& display = DisplayManager::getDisplay();

    for (std::shared_ptr<CombatEntity> combatEntity : getCombatEntities()) {
        combatEntity->update(deltaTime);
    }

    float knightX = -(getKnight()->getPosition()->getX() - 214);
    for (Terrain& terrain : getTerrains()) {
        terrain.render(knightX);
    }
}

void KnightGame::keyPressed(int key)
{
    std::shared_ptr<Knight> knight = getKnight();
    Vector2D& velocity = knight->getVelocity();

    switch (key) {
        case 0:
            knight->startRunning(Knight::RIGHT);
            break;
        case 1:
            knight->jump();
            break;
        case 2:
            knight->startRunning(Knight::LEFT);
            break;
        case 4:
            knight->attack();
    }
}

void KnightGame::setKnight(std::shared_ptr<Knight> knight) 
{
    this->knight = knight;
    addCombatEntity(knight);
}

void KnightGame::keyReleased(int key)
{
    std::shared_ptr<Knight> knight = getKnight();
    Vector2D& velocity = knight->getVelocity();

    switch (key) {
        case 0:
            knight->stopRunning(Knight::RIGHT);
            break;
        case 2:
            knight->stopRunning(Knight::LEFT);
            break;
    }
}

void KnightGame::addCombatEntity(std::shared_ptr<CombatEntity> combatEntity) 
{
    getCombatEntities().push_back(combatEntity);
}

std::vector<std::shared_ptr<CombatEntity>>& KnightGame::getCombatEntities()
{
    return combatEntities;
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

float KnightGame::calculateTerrainCollision(Rectangle& rectangle, int direction, bool returnOverlap) 
{
    for (Rectangle& terrain : getTerrains()) {
        if (rectangle.getId() != terrain.getId()) {
            float overlap = rectangle.calculateCollision(terrain, direction, returnOverlap);

            if (overlap != 0) {
                return overlap;
            }
        }
    }

    return 0;
}

void KnightGame::onGameClosed() 
{

}

std::shared_ptr<Knight> KnightGame::getKnight() 
{
    return knight;
} 

std::vector<Terrain>& KnightGame::getTerrains() 
{
    return terrains;
}