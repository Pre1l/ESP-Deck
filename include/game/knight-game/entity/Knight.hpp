#ifndef KNIGHT_HPP
#define KNIGHT_HPP

#include "Entity.hpp"
#include <TFT_eSPI.h>
#include <display/DisplayManager.hpp>
#include "game/knight-game/animation/Animation.hpp"
#include "game/knight-game/animation/AnimationObserver.hpp"

class Knight : public Entity, public AnimationObserver
{
    private:
        TFT_eSprite knightSprite = TFT_eSprite(&DisplayManager::tft);
        TFT_eSprite slashSprite = TFT_eSprite(&DisplayManager::tft);
        Hitbox hitbox;
        Animation knightAnimation;
        bool jumpRequest = false;
        bool runLeftRequest = false;
        bool runRightRequest = false;
        bool attackRequest = false;

        bool onGround = false;
        bool running = false;
        bool facingRight = true;

    public:
        Knight(std::shared_ptr<Vector2D> position);
        void update(float deltaTime) override;
        void animationCallback() override;
        Hitbox& getHitbox();
        void jump();
        void runLeft();
        void runRight();
        void stopRunLeft();
        void stopRunRight();
        void attack();

    private:
        void clearAfterImage(Vector2D& deltaVelocity);
        void handleVelocity(float deltaTime);
        void handleAnimation(float deltaTime);
};

#endif // KNIGHT_HPP