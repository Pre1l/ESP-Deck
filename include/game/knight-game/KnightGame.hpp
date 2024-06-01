#ifndef KNIGHT_GAME_HPP
#define KNIGHT_GAME_HPP

#include "game/Game.hpp"
#include "TFT_eSPI.h"
#include <vector>
#include "display/DisplayManager.hpp"
#include "game/knight-game/entity/Knight.hpp"
#include "game/knight-game/rectangle/Terrain.hpp"

class KnightGame : public Game 
{
    private:
        static std::shared_ptr<KnightGame> instance;

        std::vector<Terrain> terrains;
        std::vector<std::shared_ptr<CombatEntity>> combatEntities;
        std::shared_ptr<Knight> knight;

    public:
        static std::shared_ptr<KnightGame> getInstance();
        void update(float deltaTime) override;
        void keyPressed(int key) override;
        void keyReleased(int key) override;
        void onGameClosed() override;
        std::vector<Terrain>& getTerrains();
        std::shared_ptr<Knight> getKnight();
        float calculateTerrainCollision(Rectangle& rectangle, Rectangle::CollisionAxis axis, bool returnOverlap);
        float calculateCollision(Rectangle& rectangle, Rectangle::CollisionAxis axis, bool returnOverlap);
        std::shared_ptr<CombatEntity> calculateCombatEntityCollision(Rectangle& rectangle, Rectangle::CollisionAxis axis);
        void addCombatEntity(std::shared_ptr<CombatEntity> combatEntity);
        std::vector<std::shared_ptr<CombatEntity>>& getCombatEntities();

    private:
        KnightGame();
        void setKnight(std::shared_ptr<Knight> knight);
        friend class GameFactory;

        KnightGame(const KnightGame&) = delete;
        KnightGame& operator=(const KnightGame&) = delete;
};

#endif // KNIGHT_GAME_HPP