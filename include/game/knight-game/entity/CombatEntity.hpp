#ifndef COMBAT_ENTITY_HPP
#define COMBAT_ENTITY_HPP

#include <TFT_eSPI.h>
#include <display/DisplayManager.hpp>
#include "game/knight-game/animation/AnimationObserver.hpp"
#include "Entity.hpp"

class CombatEntity : public Entity, public AnimationObserver
{
    public:
        enum class EntityType {
            KNIGHT,
            SLIME
        };

        enum class Direction {
            RIGHT,
            LEFT
        };

    private:
        struct CombatEntityConfig
        {
            float health;
            float armor;
            float attackDamage;
            float speedX;
            float jumpSpeed;
        };

    protected:
        CombatEntityConfig config;
        EntityType type;

    private:
        bool onGround = false;
        bool running = false;
        Direction facingDirection = Direction::RIGHT;

        Vector2D velocity;
        TFT_eSprite attackSprite = TFT_eSprite(&DisplayManager::tft);
        TFT_eSprite movementSprite = TFT_eSprite(&DisplayManager::tft);
        Animation movementAnimation;

        int animationWidth;
        int animationHeight;
        int attackAnimationWidth;
        float lastOffsetX = 0;

        bool offset = true;
        bool jumpRequest = false;
        bool runLeftRequest = false;
        bool runRightRequest = false;
        bool attackRequest = false;

    public:
        void update(float offsetX, float deltaTime);
        void animationCallback() override;
        void animationFinishedCallback() override;
        Vector2D& getVelocity();
        TFT_eSprite& getAttackSprite();
        TFT_eSprite& getMovementSprite();
        int getAnimationWidth();
        int getAnimationHeight();
        int getAttackAnimationWidth();
        Animation& getMovementAnimation();
        void clearAfterImageOffset(float offsetX);
        void disableOffset();

        void jump();
        void startRunning(Direction direction);
        void stopRunning(Direction direction);
        void attack();

        bool isRunning();
        bool isOnGround();
        bool isFacingRight();
        bool isFacingLeft();

    protected:
        CombatEntity(std::shared_ptr<Vector2D> position, int animationWidth, int animationHeight, int attackAnimationWidth, Vector2D velocity);
        virtual void collisionWithCombatEntity(std::shared_ptr<CombatEntity> collisionCombatEntity, Rectangle::CollisionAxis axis) = 0;
        virtual void clearAfterImage(Vector2D& deltaVelocity);
        virtual void handleVelocity(float deltaTime);
        virtual void handleAnimation(float deltaTime);
        virtual void pushMovementSprite();
        virtual void pushAttackSprite();
        virtual void stopCallbackAnimation();
        virtual void clearCallbackAnimationAfterImage();
        virtual void setAnimation() = 0;
        //virtual void takeDamage(float amount);
};

#endif // COMBAT_ENTITY_HPP