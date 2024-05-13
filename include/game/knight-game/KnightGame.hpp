#ifndef KNIGHT_GAME_HPP
#define KNIGHT_GAME_HPP

#include "game/Game.hpp"
#include "TFT_eSPI.h"
#include <vector>
#include "display/DisplayManager.hpp"

class KnightGame : public Game 
{
    private:
        KnightGame();
        static KnightGame* instance;

    public:
        static KnightGame* getInstance();
        void update(float deltaTime) override;
        void keyPressed(int key) override;
        void keyReleased(int key) override;
        void onGameClosed() override;
};

#endif // KNIGHT_GAME_HPP