#include <TFT_eSPI.h>
#ifndef ANIMATION_HPP
#define ANIMATION_HPP

class Animation
{
    private:
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
        void update(float deltaTime);
        void setNewAnimation(const unsigned short* animationBitmap, int yIndex, int animationFrameAmount, int animationInterval);

    private:
        void pushAnimationFrame();
};

#endif // ANIMATION_HPP