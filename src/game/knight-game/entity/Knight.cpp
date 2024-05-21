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
  AnimationObserver(CallbackAnimation(knightAttackBitmap, 0, 54, 64, 5, 3, 110, knightSprite, this)),
  hitbox(getPosition(), 56, 66),
  knightAnimation(knightIdleBitmap, 0, 54, 64, 4, 200, knightSprite)
{
    knightSprite.createSprite(54, 64);
    knightSprite.setSwapBytes(true);
    knightSprite.fillRect(0, 0, 54, 64, TFT_CYAN);
    slashSprite.setSwapBytes(true);
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
    knightSprite.pushSprite(215, getPosition()->getIntY() + 1);
}

void Knight::handleVelocity(float deltaTime) 
{
    Hitbox& hitbox = getHitbox();
     std::shared_ptr<KnightGame> knightGame = KnightGame::getInstance();
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

    getPosition()->addX(deltaVelocity.getX());
    float overlapX = knightGame->calculateCollision(hitbox, Rectangle::COLLISION_X, true);

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
    float overlapY = knightGame->calculateCollision(hitbox, Rectangle::COLLISION_Y, true);

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
    /*float slashSpriteWidth = 26;
    Vector2D* position = new Vector2D(getPosition()->getX(), getPosition()->getY());
    position->addX(56);;
    Hitbox slashHitbox(position, 26, 66);

    float overlap = KnightGame::getInstance()->calculateCollision(slashHitbox, Rectangle::COLLISION_X, false);
    if (overlap == 1) {
        float overlapX = KnightGame::getInstance()->calculateCollision(slashHitbox, Rectangle::COLLISION_X, true);

        if (overlapX == 0) {
            slashSpriteWidth = 0;
        } else {
            slashSpriteWidth = 26 - overlapX;
        }
    }
    
    if (slashSpriteWidth > 0) {
        slashSprite.createSprite(slashSpriteWidth, 53);
        slashSprite.pushImage(0, 0, 26, 53, slashBitmap);
        slashSprite.pushSprite(214 + 56, position->getIntY());
        slashSprite.fillRect(0, 0, 26, 53, TFT_BLACK);
        slashSprite.pushSprite(214 + 56, position->getIntY());
        slashSprite.deleteSprite();
    }*/
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