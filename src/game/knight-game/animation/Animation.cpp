#include "game/knight-game/animation/Animation.hpp"

Animation::Animation(const unsigned short* animationBitmap, int yIndex, int animationFrameWidth, int animationFrameHeight, int animationFrameAmount, int animationInterval, TFT_eSprite& outputSprite) 
:animationBitmap(animationBitmap),
outputSprite(outputSprite)
{
    this->yIndex = yIndex;
    this->animationFrameWidth = animationFrameWidth;
    this->animationFrameHeight = animationFrameHeight;
    this->animationFrameAmount = animationFrameAmount;
    this->animationInterval = animationInterval;
}

void Animation::update(float deltaTime)
{
    animationIndex += deltaTime/animationInterval;
    if (animationIndex >= currentAnimationIndex + 1) {
        if (animationIndex > animationFrameAmount) {
            animationIndex -= animationFrameAmount;
        }
        currentAnimationIndex = floor(animationIndex);
        pushAnimationFrame();
    }
}

void Animation::setNewAnimation(const unsigned short* animationBitmap, int yIndex, int animationFrameAmount, int animationInterval) 
{
    this->animationInterval = animationInterval;
    if (animationBitmap == this->animationBitmap && yIndex == this->yIndex)
        return;
        
    this->animationBitmap = animationBitmap;
    this->yIndex = yIndex;
    this->animationFrameAmount = animationFrameAmount;

    reset();
    pushAnimationFrame();
}

void Animation::reset() 
{
    animationIndex = 0;
    currentAnimationIndex = 0;
    pushAnimationFrame();
}

void Animation::pushAnimationFrame() 
{
    if (animationInterval == -1) {
        outputSprite.pushImage(0, yIndex * -animationFrameHeight, animationFrameWidth, (yIndex + 1) * animationFrameHeight, animationBitmap);
        return;
    }

    outputSprite.pushImage(currentAnimationIndex * -animationFrameWidth, yIndex * -animationFrameHeight, animationFrameAmount * animationFrameWidth, (yIndex + 1) * animationFrameHeight, animationBitmap);
}