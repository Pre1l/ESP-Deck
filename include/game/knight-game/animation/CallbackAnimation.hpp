#ifndef CALLBACK_ANIMATION_HPP
#define CALLBACK_ANIMATION_HPP

#include "Animation.hpp"

class AnimationObserver;

class CallbackAnimation : public Animation 
{
    public:
        bool animationInProgress = false;

    private:
        AnimationObserver* observer;
        int callbackFrameIndex;

    public:
        CallbackAnimation(const unsigned short* animationBitmap, int yIndex, int animationFrameWidth, int animationFrameHeight, int animationFrameAmount, int callbackFrameIndex, int animationInterval, TFT_eSprite& outputSprite, AnimationObserver* observer);
        void update(float deltaTime) override;
        void stop();
        void setNewAnimation(const unsigned short* animationBitmap, int yIndex, int animationFrameAmount, int callbackFrameIndex, int animationInterval);
        
    private:
        void notifyObserver();
        void notifyObserverAnimationFinished();
};

#endif // CALLBACK_ANIMATION_HPP