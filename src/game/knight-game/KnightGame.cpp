#include "game/knight-game/KnightGame.hpp"
#include <game/knight-game/entity/Slime.hpp>

std::shared_ptr<KnightGame> KnightGame::instance = nullptr;

KnightGame::KnightGame() 
{
    setKnight(std::make_shared<Knight>(std::make_shared<Vector2D>(214, 0)));
    addCombatEntity(std::make_shared<Slime>(std::make_shared<Vector2D>(10, 100)));
    addCombatEntity(std::make_shared<Slime>(std::make_shared<Vector2D>(335, 0)));
    addCombatEntity(std::make_shared<Slime>(std::make_shared<Vector2D>(105, 0)));

    terrains.push_back(Terrain(std::make_shared<Vector2D>(-500, 300), 1300, 20, 0, TFT_WHITE));
    terrains.push_back(Terrain(std::make_shared<Vector2D>(200, 240), 40, 20, 0, TFT_WHITE));
    terrains.push_back(Terrain(std::make_shared<Vector2D>(300, 200), 160, 20, 0, TFT_WHITE));
    terrains.push_back(Terrain(std::make_shared<Vector2D>(100, 80), 40, 20, 0, TFT_WHITE));
    terrains.push_back(Terrain(std::make_shared<Vector2D>(170, 140), 40, 20, 0, TFT_WHITE));
    terrains.push_back(Terrain(std::make_shared<Vector2D>(-500, 0), 40, 300, 0, TFT_WHITE));
    terrains.push_back(Terrain(std::make_shared<Vector2D>(760, 0), 40, 300, 0, TFT_WHITE));
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
    float knightX = -(getKnight()->getPosition()->getX() - 214);

    removeMarkedCombatEntities();

    for (std::shared_ptr<CombatEntity> combatEntity : getCombatEntities()) {
        combatEntity->update(knightX, deltaTime);
    }

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
            knight->startRunning(Knight::Direction::RIGHT);
            break;
        case 1:
            knight->jump();
            break;
        case 2:
            knight->startRunning(Knight::Direction::LEFT);
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
            knight->stopRunning(Knight::Direction::RIGHT);
            break;
        case 2:
            knight->stopRunning(Knight::Direction::LEFT);
            break;
    }
}

void KnightGame::addCombatEntity(std::shared_ptr<CombatEntity> combatEntity) 
{
    getCombatEntities().push_back(combatEntity);
}

void KnightGame::markCombatEntityForRemoval(std::shared_ptr<CombatEntity> combatEntity) {
    combatEntitiesToRemove.push(combatEntity);
}

void KnightGame::removeMarkedCombatEntities() 
{
    while (!combatEntitiesToRemove.empty()) {
        auto combatEntityToRemove = combatEntitiesToRemove.front();
        combatEntitiesToRemove.pop();
        
        auto it = std::find(combatEntities.begin(), combatEntities.end(), combatEntityToRemove);
        if (it != combatEntities.end()) {
            combatEntities.erase(it);
        }
    }
}

std::vector<std::shared_ptr<CombatEntity>>& KnightGame::getCombatEntities()
{
    return combatEntities;
}

float KnightGame::calculateCollision(Rectangle& rectangle, Rectangle::CollisionAxis axis, bool returnOverlap) 
{ 
    for (Rectangle& terrainHitbox : getTerrains()) {
        if (rectangle.getId() != terrainHitbox.getId()) {
            float overlap = rectangle.calculateCollision(terrainHitbox, axis, returnOverlap);

            if (overlap != 0)
                return overlap;
        }
    }

    for (std::shared_ptr<CombatEntity> combatEntity : getCombatEntities()) {
        Hitbox& combatEntityHitbox = combatEntity->getHitbox();

        if (rectangle.getId() != combatEntityHitbox.getId()) {
            float overlap = rectangle.calculateCollision(combatEntityHitbox, axis, returnOverlap);

            if (overlap != 0)
                return overlap;
        }
    }

    return 0;
}

std::shared_ptr<CombatEntity> KnightGame::calculateCombatEntityCollision(Rectangle& rectangle, Rectangle::CollisionAxis axis) 
{ 
    for (std::shared_ptr<CombatEntity> combatEntity : getCombatEntities()) {
        Hitbox& combatEntityHitbox = combatEntity->getHitbox();

        if (rectangle.getId() != combatEntityHitbox.getId()) {
            int overlap = rectangle.calculateCollision(combatEntityHitbox, axis, false);

            if (overlap == 1)
                return combatEntity;
        }
    }

    return nullptr;
}

std::vector<std::shared_ptr<CombatEntity>> KnightGame::calculateCombatEntitiesCollision(Rectangle& rectangle) 
{
    std::vector<std::shared_ptr<CombatEntity>> collidingCombatEntities;

    for (std::shared_ptr<CombatEntity> combatEntity : getCombatEntities()) {
        Hitbox& combatEntityHitbox = combatEntity->getHitbox();

        if (rectangle.getId() != combatEntityHitbox.getId()) {
            int overlap = rectangle.calculateCollision(combatEntityHitbox);

            if (overlap == 1)
                collidingCombatEntities.push_back(combatEntity);
        }
    }

    return collidingCombatEntities;
}

float KnightGame::calculateTerrainCollision(Rectangle& rectangle, Rectangle::CollisionAxis axis, bool returnOverlap) 
{
    for (Rectangle& terrain : getTerrains()) {
        if (rectangle.getId() != terrain.getId()) {
            float overlap = rectangle.calculateCollision(terrain, axis, returnOverlap);

            if (overlap != 0)
                return overlap;
        }
    }

    return 0;
}

void KnightGame::onGameClosed() 
{
    instance.reset();
}

std::shared_ptr<Knight> KnightGame::getKnight() 
{
    return knight;
} 

std::vector<Terrain>& KnightGame::getTerrains() 
{
    return terrains;
}