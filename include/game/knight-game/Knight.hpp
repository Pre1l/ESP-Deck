#ifndef KNIGHT_HPP
#define KNIGHT_HPP

#include "TFT_eSPI.h"
#include "display/DisplayManager.hpp"
#include <math/Vector2D.hpp>

class Knight 
{
    public:
        static const int IDLE = 0;
        static const int RUNNING_RIGHT = 1;
        static const int RUNNING_LEFT = 2;

    private:
        const int pixelSpeed = 2;
        TFT_eSprite knightSprite = TFT_eSprite(&DisplayManager::tft);
        Vector2D position;
        int animationIndex;
        int animationDelayCounter;
        int state;

    public:
        Knight();
        void update(float deltatime);
        void attack();
        void jump();
        void setState(int state);
};

#endif // KNIGHT_HPP