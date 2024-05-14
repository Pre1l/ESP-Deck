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
        bool onGround = false;
        bool jumpRequest = false;
        bool runLeftRequest = false;
        bool runLeftCheck = false;
        bool runRightRequest = false;
        bool runRightCheck = false;

    public:
        Knight(Vector2D position);
        void update(float deltaTime) override;
        Hitbox& getHitbox();
        void jump();
        void runLeft();
        void runRight();
        void stopRunLeft();
        void stopRunRight();
};

#endif // KNIGHT_HPP