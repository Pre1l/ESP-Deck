#ifndef COMBAT_ENTITY_HPP
#define COMBAT_ENTITY_HPP

#include <TFT_eSPI.h>
#include <display/DisplayManager.hpp>
#include "game/knight-game/animation/AnimationObserver.hpp"
#include "Entity.hpp"

class CombatEntity : public Entity, public AnimationObserver
{
    public:
        const int RIGHT = 0;
        const int LEFT = 1;

    protected:
        bool onGround = false;
        bool running = false;
        int facingDirection = RIGHT;

    private:
        Vector2D velocity;
        TFT_eSprite attackSprite = TFT_eSprite(&DisplayManager::tft);
        TFT_eSprite movementSprite = TFT_eSprite(&DisplayManager::tft);
        Animation movementAnimation;

        int animationWidth;
        int animationHeight;
        int attackAnimationWidth;

        bool jumpRequest = false;
        bool runLeftRequest = false;
        bool runRightRequest = false;
        bool attackRequest = false;

    public:
        void update(float deltaTime);
        void animationCallback() override;
        void animationFinishedCallback() override;
        Vector2D& getVelocity();
        TFT_eSprite& getAttackSprite();
        TFT_eSprite& getMovementSprite();
        int getAnimationWidth();
        int getAnimationHeight();
        int getAttackAnimationWidth();
        Animation& getMovementAnimation();

        void jump();
        void startRunning(int direction);
        void stopRunning(int direction);
        void attack();

    protected:
        CombatEntity(std::shared_ptr<Vector2D> position, int animationWidth, int animationHeight, int attackAnimationWidth, Vector2D velocity);
        virtual void clearAfterImage(Vector2D& deltaVelocity);
        virtual void handleVelocity(float deltaTime);
        virtual void handleAnimation(float deltaTime);
        virtual void pushMovementSprite();
        virtual void pushAttackSprite();
        virtual void stopCallbackAnimation();
        virtual void clearCallbackAnimationAfterImage();
        virtual void setAnimation() = 0;
};

#endif // COMBAT_ENTITY_HPP