#include "game/knight-game/entity/Knight.hpp"

#include "bitmap/knight-game/KnightIdleBitmap.hpp"
#include "bitmap/knight-game/KnightRunRightBitmap.hpp"
#include "bitmap/knight-game/KnightRunLeftBitmap.hpp"
#include "bitmap/knight-game/KnightAttackBitmap.hpp"
#include "bitmap/knight-game/SlashBitmap.hpp"
#include <game/knight-game/KnightGame.hpp>
#include "bitmap/knight-game/KnightJumpBitmap.hpp"
#include <game/knight-game/animation/CallbackAnimation.hpp>
#include <game/knight-game/animation/AnimationObserver.hpp>
#include <memory>

Knight::Knight(std::shared_ptr<Vector2D> position) 
: Entity(position, Vector2D(0, 0)),
  AnimationObserver(CallbackAnimation(knightAttackBitmap, 0, 64, 64, 6, 4, 90, attackSprite, this)),
  hitbox(getPosition(), 56, 66),
  knightAnimation(knightIdleBitmap, 0, 54, 64, 4, 200, knightSprite)
{
    knightSprite.createSprite(54, 64);
    knightSprite.setSwapBytes(true);
    knightSprite.fillRect(0, 0, 54, 64, TFT_CYAN);
    attackSprite.createSprite(64, 64);
    attackSprite.setSwapBytes(true);
}

void Knight::update(float deltaTime) {
    if (attackRequest) {
        attackRequest = false;

        Hitbox attackHitbox(std::make_shared<Vector2D>(getPosition()->getX() + 56, getPosition()->getY()), 9, 66);
        if (KnightGame::getInstance()->calculateTerrainCollision(attackHitbox, Rectangle::COLLISION_X, false) == 0) {
            callbackAnimation.setNewAnimation(knightAttackBitmap, 0, 5, 90);
            callbackAnimation.update(deltaTime);
        }
    }

    handleVelocity(deltaTime);
    handleAnimation(deltaTime);

    if (callbackAnimation.animationInProgress) {
        pushAttackSprite();
    } else {
        pushSprite();
    }
}

void Knight::pushSprite() 
{
    knightSprite.pushSprite(215, getPosition()->getIntY() + 1);
}

void Knight::pushAttackSprite() 
{
    attackSprite.pushSprite(215, getPosition()->getIntY() + 1);
}

void Knight::handleVelocity(float deltaTime) 
{
    Hitbox& hitbox = getHitbox();
     std::shared_ptr<KnightGame> knightGame = KnightGame::getInstance();
    Vector2D& velocity = getVelocity();

    velocity.addY(0.05);
    if (jumpRequest == true) {
        velocity.subtractY(0.7);
        jumpRequest = false;
        stopCallbackAnimation();
    }

    if (runRightRequest && runLeftRequest) {
        velocity.setX(0);
        running = false;
    } else if (runRightRequest) {
        velocity.setX(0.2);
        facingRight = true;
        running = true;
        stopCallbackAnimation();
    } else if (runLeftRequest) {
        velocity.setX(-0.2);
        facingRight = false;
        running = true;
        stopCallbackAnimation();
    } else {
        velocity.setX(0);
        running = false;
    }

    Vector2D deltaVelocity = velocity.copy().multiply(deltaTime);
    clearAfterImage(deltaVelocity);

    getPosition()->addX(deltaVelocity.getX());
    float overlapX = knightGame->calculateTerrainCollision(hitbox, Rectangle::COLLISION_X, true);

    if (deltaVelocity.getX() > 0 && overlapX != 0) {
        getPosition()->subtractX(overlapX);
        velocity.setX(0);
        running = false;
    } else if (deltaVelocity.getX() < 0 && overlapX != 0) {
        getPosition()->addX(overlapX);
        velocity.setX(0);
        running = false;
    }

    getPosition()->addY(deltaVelocity.getY());
    float overlapY = knightGame->calculateTerrainCollision(hitbox, Rectangle::COLLISION_Y, true);

    if (deltaVelocity.getY() > 0 && overlapY != 0) {
        getPosition()->subtractY(overlapY);
        velocity.setY(0);
        onGround = true;
    } else if (deltaVelocity.getY() < 0 && overlapY != 0) {
        getPosition()->addY(overlapY);
        velocity.setY(0);
    } else {
        onGround = false;
    }
}

void Knight::stopCallbackAnimation() 
{
    if (callbackAnimation.animationInProgress) {
        callbackAnimation.stop();
        clearCallbackAnimationAfterImage();
    }
}

void Knight::clearAfterImage(Vector2D& deltaVelocity) 
{
    TFT_eSPI& display = DisplayManager::getDisplay();

    if (deltaVelocity.getY() > 0) {
        display.fillRect(/*ceil(getPosition()->getIntX())*/ 215, ceil(getPosition()->getY()), 54, ceil(deltaVelocity.getIntY()) + 1, TFT_BLACK);
    } else if (deltaVelocity.getY() < 0) {
        display.fillRect(/*ceil(getPosition()->getIntX())*/ 215, ceil(getPosition()->getY() + 64 + deltaVelocity.getIntY()), 54, ceil(-deltaVelocity.getY()) + 1, TFT_BLACK);
    }

    /*if (deltaVelocity.getX() > 0) {
        display.fillRect(ceil(getPosition()->getIntX()) - 1, ceil(getPosition()->getIntY()), ceil(deltaVelocity.getX()) + 1, 65, TFT_BLACK);
    } else if (deltaVelocity.getX() < 0) {
        display.fillRect(ceil(getPosition()->getIntX()) + 54 + ceil(deltaVelocity.getX()) - 1, ceil(getPosition()->getIntY()), ceil(-deltaVelocity.getX()) + 1, 65, TFT_BLACK);
    }*/
}

void Knight::handleAnimation(float deltaTime) 
{
    if (callbackAnimation.animationInProgress) {
        callbackAnimation.update(deltaTime);
        return;
    }

    if (onGround) {
        if (running) {
            if (facingRight) {
                knightAnimation.setNewAnimation(knightRunRightBitmap, 0, 7, 100);
            } else {
                knightAnimation.setNewAnimation(knightRunLeftBitmap, 0, 7, 100);
            }
        } else {
            if (facingRight) {
                knightAnimation.setNewAnimation(knightIdleBitmap, 0, 2, 250);
            } else {
                knightAnimation.setNewAnimation(knightIdleBitmap, 1, 2, 250);
            }
        }
    } else {
        if (facingRight) {
            knightAnimation.setNewAnimation(knightJumpBitmap, 0, 0, -1);
        } else {
            knightAnimation.setNewAnimation(knightJumpBitmap, 1, 0, -1);
        }
    }

    knightAnimation.update(deltaTime);
}

void Knight::animationCallback()
{
    // Do damage
}

void Knight::animationFinishedCallback() 
{
    clearCallbackAnimationAfterImage();
}

void Knight::clearCallbackAnimationAfterImage() 
{
    DisplayManager::getDisplay().fillRect(215 + 54, getPosition()->getIntY() + 1, 10, 64, TFT_BLACK);
}

void Knight::attack()
{
    if (onGround) {
        attackRequest = true;
        stopRunLeft();
        stopRunRight();
    }
}

void Knight::jump() 
{
    if (onGround) {
        jumpRequest = true;
    }
}

void Knight::runLeft() 
{
    runLeftRequest = true;
}

void Knight::runRight() 
{
    runRightRequest = true;
}

void Knight::stopRunLeft() 
{
    runLeftRequest = false;
}

void Knight::stopRunRight() 
{
    runRightRequest = false;
}

Hitbox& Knight::getHitbox() 
{
    return hitbox;
}