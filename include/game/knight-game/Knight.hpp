#ifndef KNIGHT_HPP
#define KNIGHT_HPP

#include "Entity.hpp"
#include <TFT_eSPI.h>
#include <display/DisplayManager.hpp>

class Knight : public Entity
{
    private:
        TFT_eSprite knightSprite = TFT_eSprite(&DisplayManager::tft);
        Hitbox hitbox;

    public:
        Knight(Vector2D& position);
        void update(float deltaTime) override;
        Hitbox& getHitbox();
};

#endif // KNIGHT_HPP