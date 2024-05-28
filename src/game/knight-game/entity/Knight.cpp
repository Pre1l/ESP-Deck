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
: CombatEntity(position, 54, 64, 64, Vector2D(0, 0))
{
    getMovementAnimation().setNewAnimation(knightIdleBitmap, 0, 4, 200);
    callbackAnimation.setNewAnimation(knightAttackBitmap, 0, 6, 4, 90);
}

void Knight::pushMovementSprite() 
{
    getMovementSprite().pushSprite(215, getPosition()->getIntY() + 1);
}

void Knight::pushAttackSprite() 
{
    getAttackSprite().pushSprite(215, getPosition()->getIntY() + 1);
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

void Knight::setAnimation() 
{
    Animation& movementAnimation = getMovementAnimation();

    if (onGround) {
        if (running) {
            facingDirection == RIGHT ? movementAnimation.setNewAnimation(knightRunRightBitmap, 0, 7, 100) : movementAnimation.setNewAnimation(knightRunLeftBitmap, 0, 7, 100);
        } else {
            facingDirection == RIGHT ? movementAnimation.setNewAnimation(knightIdleBitmap, 0, 2, 250) : movementAnimation.setNewAnimation(knightIdleBitmap, 1, 2, 250);
        }
    } else {
        facingDirection == RIGHT ? movementAnimation.setNewAnimation(knightJumpBitmap, 0, 0, -1) : movementAnimation.setNewAnimation(knightJumpBitmap, 1, 0, -1) ;
    }
}

void Knight::clearCallbackAnimationAfterImage() 
{
    DisplayManager::getDisplay().fillRect(215 + 54, getPosition()->getIntY() + 1, 10, 64, TFT_BLACK);
}