#ifndef ANIMATION_OBSERVER_HPP
#define ANIMATION_OBSERVER_HPP

#include "CallbackAnimation.hpp"

class AnimationObserver 
{
    public:
        virtual void animationCallback() = 0;
        virtual void animationFinishedCallback() = 0;
        virtual ~AnimationObserver() {}
};

#endif // ANIMATION_OBSERVER_HPP