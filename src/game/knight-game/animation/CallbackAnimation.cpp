#include "game/knight-game/animation/CallbackAnimation.hpp"

#include "game/knight-game/animation/AnimationObserver.hpp"

CallbackAnimation::CallbackAnimation(const unsigned short* animationBitmap, int yIndex, int animationFrameWidth, int animationFrameHeight, int animationFrameAmount, int animationInterval, TFT_eSprite& outputSprite, AnimationObserver* observer) 
: Animation(animationBitmap, yIndex, animationFrameWidth, animationFrameHeight, animationFrameAmount, animationInterval, outputSprite),
  observer(observer)
{

}

void CallbackAnimation::notifyObserver() 
{
    callbackInProgress = false;
    observer->animationCallback();
}

void CallbackAnimation::update(float deltaTime) 
{
    callbackInProgress = true;
    animationIndex += deltaTime/animationInterval;
    if (animationIndex >= currentAnimationIndex + 1) {
        if (animationIndex > animationFrameAmount) {
            animationIndex -= animationFrameAmount;
            notifyObserver();
        }
        currentAnimationIndex = floor(animationIndex);
        pushAnimationFrame();
    }
}

void CallbackAnimation::stop() 
{
    reset();
    callbackInProgress = false;
}