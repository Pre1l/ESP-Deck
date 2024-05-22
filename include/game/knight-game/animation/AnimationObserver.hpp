#ifndef ANIMATION_OBSERVER_HPP
#define ANIMATION_OBSERVER_HPP

#include "CallbackAnimation.hpp"

class AnimationObserver 
{
    protected:
        CallbackAnimation callbackAnimation;

    public:
        virtual void animationCallback() = 0;
        virtual void animationFinishedCallback() = 0;
        virtual ~AnimationObserver() {}

    protected:
        AnimationObserver(CallbackAnimation callbackAnimation) : callbackAnimation(callbackAnimation) {}
};

#endif // ANIMATION_OBSERVER_HPP