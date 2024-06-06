#ifndef COMBAT_ENTITY_HPP
#define COMBAT_ENTITY_HPP

#include <TFT_eSPI.h>
#include <display/DisplayManager.hpp>
#include "game/knight-game/animation/AnimationObserver.hpp"
#include "Entity.hpp"
#include <game/knight-game/rectangle/ProxyHitbox.hpp>

class CombatEntity : public Entity, public AnimationObserver
{
    public:
        enum class Type {
            KNIGHT,
            SLIME
        };

        enum class Direction {
            RIGHT,
            LEFT
        };

    private:
        struct CombatEntityStats
        {
            float health;
            float armor;
            float attackDamage;
            float speedX;
            float jumpSpeed;
        };

    protected:
        CombatEntityStats stats;
        Type type;

    private:
        static uint8_t nextId;
        uint8_t id;

        Direction facingDirection = Direction::RIGHT;
        Vector2D velocity;

        TFT_eSprite attackSprite = TFT_eSprite(&DisplayManager::tft);
        TFT_eSprite deathSprite = TFT_eSprite(&DisplayManager::tft);
        TFT_eSprite movementSprite = TFT_eSprite(&DisplayManager::tft);

        Animation movementAnimation;
        CallbackAnimation attackAnimation;
        CallbackAnimation deathAnimation;

        ProxyHitbox attackHitboxRight;
        ProxyHitbox attackHitboxLeft;

        int animationWidth;
        int animationHeight;
        int attackAnimationWidth;
        float lastOffsetX = 0;

        bool offset = true;
        bool dead = false;
        bool onGround = false;
        bool running = false;

        bool jumpRequest = false;
        bool runLeftRequest = false;
        bool runRightRequest = false;
        bool attackRequest = false;

    public:
        void update(float offsetX, float deltaTime) override;
        void animationCallback() override;
        void animationFinishedCallback() override;

        Vector2D& getVelocity();
        Type getType();
        uint8_t getId();

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
        void disableOffset();

        CallbackAnimation& getAttackAnimation();
        CallbackAnimation& getDeathAnimation();
        Animation& getMovementAnimation();
        TFT_eSprite& getAttackSprite();
        TFT_eSprite& getMovementSprite();
        TFT_eSprite& getDeathSprite();
        int getAnimationWidth();
        int getAnimationHeight();
        int getAttackAnimationWidth();

        virtual void collisionWithCombatEntity(std::shared_ptr<CombatEntity> collisionCombatEntity, Rectangle::CollisionAxis axis) = 0;
        virtual void setAnimation() = 0;
        virtual void setAttackAnimation() = 0;
        virtual void setDeathAnimation() = 0;

        virtual void clearAfterImageVelocity(Vector2D& deltaVelocity);
        virtual void clearAfterImageOffset(float offsetX);
        virtual void clearAfterImageAttackAnimation();
        virtual void clearAfterImageDeath();

        virtual void handleVelocity(float deltaTime);
        virtual void handleAnimation(float deltaTime);
        virtual void pushMovementSprite();
        virtual void pushAttackSprite();
        virtual void pushDeathSprite();
        virtual void stopCallbackAnimation();
        virtual void takeDamage(float amount);
        virtual void die();
};

#endif // COMBAT_ENTITY_HPP