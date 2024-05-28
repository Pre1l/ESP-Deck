#include "game/knight-game/animation/CallbackAnimation.hpp"

#include "game/knight-game/animation/AnimationObserver.hpp"

CallbackAnimation::CallbackAnimation(const unsigned short* animationBitmap, int yIndex, int animationFrameWidth, int animationFrameHeight, int animationFrameAmount, int callbackFrameIndex, int animationInterval, TFT_eSprite& outputSprite, AnimationObserver* observer) 
: Animation(animationBitmap, yIndex, animationFrameWidth, animationFrameHeight, animationFrameAmount, animationInterval, outputSprite),
  observer(observer)
{
    if (callbackFrameIndex < 0 || callbackFrameIndex >= animationFrameAmount) {
        this->callbackFrameIndex = animationFrameAmount - 1;
    } else {
        this->callbackFrameIndex = callbackFrameIndex;
    }
}

void CallbackAnimation::notifyObserver() 
{
    observer->animationCallback();
}

void CallbackAnimation::notifyObserverAnimationFinished() 
{
    observer->animationFinishedCallback();
}

void CallbackAnimation::setNewAnimation(const unsigned short* animationBitmap, int yIndex, int animationFrameAmount, int callbackFrameIndex, int animationInterval) 
{
    this->callbackFrameIndex = callbackFrameIndex;
    Animation::setNewAnimation(animationBitmap, yIndex, animationFrameAmount, animationInterval);
}

void CallbackAnimation::update(float deltaTime) 
{
    animationInProgress = true;
    animationIndex += deltaTime/animationInterval;
    if (animationIndex >= currentAnimationIndex + 1) {
        if (floor(animationIndex) == callbackFrameIndex) {
            notifyObserver();
        }

        if (animationIndex > animationFrameAmount) {
            animationIndex -= animationFrameAmount;
            animationInProgress = false;
            notifyObserverAnimationFinished();
        }

        currentAnimationIndex = floor(animationIndex);
        pushAnimationFrame();
    }
}

void CallbackAnimation::stop() 
{
    reset();
    animationInProgress = false;
}