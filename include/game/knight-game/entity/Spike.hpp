#ifndef SPIKE_HPP
#define SPIKE_HPP

#include <TFT_eSPI.h>
#include "display/DisplayManager.hpp"
#include "Entity.hpp"

class Spike : public Entity 
{
    private:
        TFT_eSprite spikeSprite = TFT_eSprite(&DisplayManager::tft);

    public:
        Spike(std::shared_ptr<Vector2D> position, int spikeAmount);
        void update(float offsetX, float deltaTime) override;

    private:
        TFT_eSprite& getSpikeSprite();
        void pushSpikeSprite();
};

#endif // SPIKE_HPP