#include "game/knight-game/entity/Knight.hpp"

#include "bitmap/knight-game/KnightIdleBitmap.hpp"
#include "bitmap/knight-game/KnightRunRightBitmap.hpp"
#include "bitmap/knight-game/KnightRunLeftBitmap.hpp"
#include "bitmap/knight-game/KnightAttackBitmap.hpp"
#include <game/knight-game/KnightGame.hpp>
#include "bitmap/knight-game/KnightJumpBitmap.hpp"
#include <game/knight-game/animation/CallbackAnimation.hpp>
#include <game/knight-game/animation/AnimationObserver.hpp>

Knight::Knight(Vector2D position) 
: Entity(position, Vector2D(0, 0)),
  AnimationObserver(CallbackAnimation(knightAttackBitmap, 0, 54, 64, 5, 110, knightSprite, this)),
  hitbox(&getPosition(), 54, 64),
  knightAnimation(knightIdleBitmap, 0, 54, 64, 4, 200, knightSprite)
{
    knightSprite.createSprite(54, 64);
    knightSprite.setSwapBytes(true);
    knightSprite.fillRect(0, 0, 54, 64, TFT_CYAN);
}

void Knight::update(float deltaTime) {
    if (attackRequest) {
        attackRequest = false;
        if (facingRight) {
            callbackAnimation.setNewAnimation(knightAttackBitmap, 0, 5, 110);
        } else {
            callbackAnimation.setNewAnimation(knightAttackBitmap, 1, 5, 110);
        }
        callbackAnimation.update(deltaTime);
    }
    handleVelocity(deltaTime);
    handleAnimation(deltaTime);
    knightSprite.pushSprite(getPosition().getIntX(), getPosition().getIntY());
}

void Knight::handleVelocity(float deltaTime) 
{
    Hitbox& hitbox = getHitbox();
    KnightGame* knightGame = KnightGame::getInstance();
    Vector2D& velocity = getVelocity();

    velocity.addY(0.05);
    if (jumpRequest == true) {
        velocity.subtractY(0.7);
        callbackAnimation.stop();
        jumpRequest = false;
    }


    if (runRightRequest && runLeftRequest) {
        velocity.setX(0);
        running = false;
    } else if (runRightRequest) {
        velocity.setX(0.2);
        facingRight = true;
        callbackAnimation.stop();
        running = true;
    } else if (runLeftRequest) {
        velocity.setX(-0.2);
        facingRight = false;
        callbackAnimation.stop();
        running = true;
    } else {
        velocity.setX(0);
        running = false;
    }

    Vector2D deltaVelocity = velocity.copy().multiply(deltaTime);
    clearAfterImage(deltaVelocity);

    getPosition().addX(deltaVelocity.getX());
    float overlapX = knightGame->calculateCollision(hitbox, Rectangle::COLLISION_X);

    if (deltaVelocity.getX() > 0 && overlapX != 0) {
        getPosition().subtractX(overlapX);
        velocity.setX(0);
        running = false;
    } else if (deltaVelocity.getX() < 0 && overlapX != 0) {
        getPosition().addX(overlapX);
        velocity.setX(0);
        running = false;
    }

    getPosition().addY(deltaVelocity.getY());
    float overlapY = knightGame->calculateCollision(hitbox, Rectangle::COLLISION_Y);

    if (deltaVelocity.getY() > 0 && overlapY != 0) {
        getPosition().subtractY(overlapY);
        velocity.setY(0);
        onGround = true;
    } else if (deltaVelocity.getY() < 0 && overlapY != 0) {
        getPosition().addY(overlapY);
        velocity.setY(0);
    } else {
        onGround = false;
    }
}

void Knight::clearAfterImage(Vector2D& deltaVelocity) 
{
    TFT_eSPI& display = DisplayManager::getDisplay();

    if (deltaVelocity.getY() > 0) {
        display.fillRect(ceil(getPosition().getIntX()), ceil(getPosition().getY()) - 1, 55, ceil(deltaVelocity.getIntY()) + 1, TFT_BLACK);
    } else if (deltaVelocity.getY() < 0) {
        display.fillRect(ceil(getPosition().getIntX()), ceil(getPosition().getY() + 64 + deltaVelocity.getIntY()) - 1, 55, ceil(-deltaVelocity.getY()) + 1, TFT_BLACK);
    }

    if (deltaVelocity.getX() > 0) {
        display.fillRect(ceil(getPosition().getIntX()) - 1, ceil(getPosition().getIntY()), ceil(deltaVelocity.getX()) + 1, 65, TFT_BLACK);
    } else if (deltaVelocity.getX() < 0) {
        display.fillRect(ceil(getPosition().getIntX()) + 54 + ceil(deltaVelocity.getX()) - 1, ceil(getPosition().getIntY()), ceil(-deltaVelocity.getX()) + 1, 65, TFT_BLACK);
    }
}

void Knight::handleAnimation(float deltaTime) 
{
    if (callbackAnimation.callbackInProgress) {
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