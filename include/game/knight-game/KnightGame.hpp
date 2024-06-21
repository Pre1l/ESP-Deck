#ifndef KNIGHT_GAME_HPP
#define KNIGHT_GAME_HPP

#include "game/Game.hpp"
#include "TFT_eSPI.h"
#include <queue>
#include <vector>
#include "display/DisplayManager.hpp"
#include "game/knight-game/entity/Knight.hpp"
#include "game/knight-game/rectangle/Terrain.hpp"
#include "entity/Spike.hpp"

class KnightGame : public Game 
{
    private:
        std::vector<Terrain> terrains;
        std::vector<Spike> spikes;
        std::vector<std::shared_ptr<CombatEntity>> combatEntities;
        std::queue<std::shared_ptr<CombatEntity>> combatEntitiesToRemove;
        std::shared_ptr<Knight> knight;

    public:
        KnightGame();

        void update(float deltaTime) override;
        void keyPressed(Core::Key key) override;
        void keyReleased(Core::Key key) override;

        void addCombatEntity(std::shared_ptr<CombatEntity> combatEntity);
        void removeMarkedCombatEntities();
        void markCombatEntityForRemoval(std::shared_ptr<CombatEntity> combatEntity);

        std::vector<Terrain>& getTerrains();
        std::vector<Spike>& getSpikes();
        std::shared_ptr<Knight> getKnight();
        std::vector<std::shared_ptr<CombatEntity>>& getCombatEntities();

        float calculateTerrainCollision(Rectangle& rectangle, Rectangle::CollisionAxis axis, bool returnOverlap);
        float calculateCollision(Rectangle& rectangle, Rectangle::CollisionAxis axis, bool returnOverlap);
        std::shared_ptr<CombatEntity> calculateCombatEntityCollision(Rectangle& rectangle, Rectangle::CollisionAxis axis);
        std::vector<std::shared_ptr<CombatEntity>> calculateCombatEntitiesCollision(Rectangle& rectangle);

    private:
        void setKnight(std::shared_ptr<Knight> knight);

        KnightGame(const KnightGame&) = delete;
        KnightGame& operator=(const KnightGame&) = delete;
};

#endif // KNIGHT_GAME_HPP