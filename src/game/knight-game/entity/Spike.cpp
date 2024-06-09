#include "game/knight-game/entity/Spike.hpp"

#include "bitmap/knight-game/SpikeBitmap.hpp"

Spike::Spike(std::shared_ptr<Vector2D> position, int spikeAmount) 
: Entity(position, Hitbox(position, spikeAmount * 5 + 2, 12))
{
    spikeSprite.setSwapBytes(true);
    int fickDich = spikeAmount * 5;
    spikeSprite.createSprite(fickDich, 10);
    spikeSprite.fillSprite(TFT_CYAN);

    /*for (int indexX = 0; indexX < spikeAmount; indexX++) {
        int spriteDrawOffset = indexX * 5; 

        spikeSprite.pushImage(spriteDrawOffset, 0, 5, 10, spikeBitmap);
    }*/

    pushSpikeSprite();
}

void Spike::update(float offsetX, float deltaTime) 
{
    float movementX = offsetX - getOffsetX();

    Entity::update(offsetX, deltaTime);

    if (movementX != 0) {
        pushSpikeSprite();
    }

}

TFT_eSprite& Spike::getSpikeSprite() 
{
    return spikeSprite;
}

void Spike::pushSpikeSprite() 
{
    spikeSprite.pushSprite(round(getPosition()->getX() + getOffsetX()) + 1, getPosition()->getIntY() + 1);
}