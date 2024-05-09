#ifndef KNIGHT_GAME_HPP
#define KNIGHT_GAME_HPP

#include "game/Game.hpp"
#include "TFT_eSPI.h"
#include "display/DisplayManager.hpp"
#include "Knight.hpp"

class KnightGame : public Game 
{
    private:
        TFT_eSprite knightWalkSpriteSheet = TFT_eSprite(&DisplayManager::tft);
        Knight knight;

    public:
        KnightGame();
        void update() override;
        void keyPressed(int key) override;
        void keyReleased(int key) override;
        void onGameClosed();
};

#endif // KNIGHT_GAME_HPP