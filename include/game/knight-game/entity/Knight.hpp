#ifndef KNIGHT_HPP
#define KNIGHT_HPP

#include "Entity.hpp"
#include <TFT_eSPI.h>
#include <display/DisplayManager.hpp>
#include "game/knight-game/animation/Animation.hpp"

class Knight : public Entity
{
    private:
        TFT_eSprite knightSprite = TFT_eSprite(&DisplayManager::tft);
        Hitbox hitbox;
        Animation knightAnimation;
        bool onGround = false;
        bool running = false;
        bool jumpRequest = false;
        bool runLeftRequest = false;
        bool runRightRequest = false;
        bool facingRight = true;
        bool invert = false;

    public:
        Knight(Vector2D position);
        void update(float deltaTime) override;
        Hitbox& getHitbox();
        void jump();
        void runLeft();
        void runRight();
        void stopRunLeft();
        void stopRunRight();

    private:
        void clearAfterImage(Vector2D& deltaVelocity);
        void handleVelocity(float deltaTime);
        void handleAnimation(float deltaTime);
};

#endif // KNIGHT_HPP