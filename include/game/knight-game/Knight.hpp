#ifndef KNIGHT_HPP
#define KNGIHT_HPP

#include "Entity.hpp"
#include <TFT_eSPI.h>
#include <display/DisplayManager.hpp>

class Knight : public Entity
{
    private:
        TFT_eSprite knightSprite = TFT_eSprite(&DisplayManager::tft);

    public:
        Knight(Vector2D& position);
        void update(float deltaTime) override;
};

#endif // KNIGHT_HPP