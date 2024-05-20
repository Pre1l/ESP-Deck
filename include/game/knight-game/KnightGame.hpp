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
        static KnightGame* instance;

        std::vector<Terrain> terrains;
        Knight* knight;

    public:
        static KnightGame* getInstance();
        void update(float deltaTime) override;
        void keyPressed(int key) override;
        void keyReleased(int key) override;
        void onGameClosed() override;
        std::vector<Terrain>& getTerrains();
        Knight* getKnight();
        float calculateCollision(Rectangle& rectangle, int direction, bool returnOverlap);

    private:
        KnightGame();
};

#endif // KNIGHT_GAME_HPP