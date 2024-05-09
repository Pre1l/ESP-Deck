#include "game/knight-game/Knight.hpp"

#include "bitmap/knight-game/KnightRunRightBitmap.hpp"
#include "bitmap/knight-game/KnightRunLeftBitmap.hpp"
#include "bitmap/knight-game/KnightIdleBitmap.hpp"

Knight::Knight()
{
    setState(IDLE);
    Vector2D position(0, 0);
    knightSprite.createSprite(54, 64);
    knightSprite.setSwapBytes(true);
}

void Knight::update(float deltaTime) 
{
    TFT_eSPI& display = DisplayManager::getDisplay();
    animationDelayCounter++;
    if (animationDelayCounter > 6) {
        animationIndex++;
        animationDelayCounter = 0;
    }

    switch (state) {
        case 0:
            if (animationIndex > 3)
                animationIndex = 0;
            knightSprite.pushImage(animationIndex*-54, 0, 216, 64, knightIdleBitmap);
            break;
        case 1:
            if (animationIndex > 6)
                animationIndex = 0;
            display.fillRect(position.getIntX(), position.getIntY(), 2, 64, TFT_BLACK);

            position.addX(2);
            knightSprite.pushImage(animationIndex*-54, 0, 378, 64, knightRunRightBitmap);
            break;
        case 2:
            if (animationIndex > 6)
                animationIndex = 0;
            display.fillRect(position.getIntX() + 54 - 2, position.getIntY(), 2, 64, TFT_BLACK);

            position.subtractX(2);
            knightSprite.pushImage(animationIndex*-54, 0, 378, 64, knightRunLeftBitmap);
            break;
    }

    knightSprite.pushSprite(position.getIntX(), position.getIntY());
}

void Knight::setState(int state) 
{
    this->state = state;
    animationIndex = 0;
}

void Knight::attack() 
{

}

void Knight::jump() 
{

}