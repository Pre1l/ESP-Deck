#ifndef ANIMATION_HPP
#define ANIMATION_HPP

#include <TFT_eSPI.h>

class Animation
{
    protected:
        const unsigned short* animationBitmap;
        int animationFrameWidth;
        int animationFrameHeight;
        int yIndex;
        int animationFrameAmount;
        int animationInterval;
        TFT_eSprite& outputSprite;
        float animationIndex = 0;
        int currentAnimationIndex = 0;

    public:
        Animation(const unsigned short* animationBitmap, int yIndex, int animationFrameWidth, int animationFrameHeight, int animationFrameAmount, int animationInterval, TFT_eSprite& outputSprite);
        virtual void update(float deltaTime);
        void setNewAnimation(const unsigned short* animationBitmap, int yIndex, int animationFrameAmount, int animationInterval);

    protected:
        void pushAnimationFrame();
};

#endif // ANIMATION_HPP