#include "game/knight-game/entity/Knight.hpp"

#include "bitmap/knight-game/KnightIdleBitmap.hpp"
#include "bitmap/knight-game/KnightRunRightBitmap.hpp"
#include "bitmap/knight-game/KnightRunLeftBitmap.hpp"
#include "bitmap/knight-game/KnightAttackBitmap.hpp"
#include <game/knight-game/KnightGame.hpp>
#include "bitmap/knight-game/KnightJumpBitmap.hpp"
#include <game/knight-game/animation/CallbackAnimation.hpp>
#include <game/knight-game/animation/AnimationObserver.hpp>
#include <memory>

Knight::Knight(std::shared_ptr<Vector2D> position) 
: CombatEntity(position, 54, 64, 64, Vector2D(0, 0))
{
    type = Type::KNIGHT;

    stats.speedX = 0.2;
    stats.jumpSpeed = 0.7;
    stats.attackDamage = 25;
    
    disableOffset();
    getMovementAnimation().setNewAnimation(knightIdleBitmap, 0, 4, 200);
    getAttackAnimation().setNewAnimation(knightAttackBitmap, 0, 6, 4, 90);
}

void Knight::pushMovementSprite() 
{
    getMovementSprite().pushSprite(215, getPosition()->getIntY() + 1);
}

void Knight::pushAttackSprite() 
{
    if (isFacingRight()) {
        getAttackSprite().pushSprite(215, getPosition()->getIntY() + 1);
        return;        
    }

    getAttackSprite().pushSprite(205, getPosition()->getIntY() + 1);
}

void Knight::clearAfterImageVelocity(Vector2D& deltaVelocity) 
{
    TFT_eSPI& display = DisplayManager::getDisplay();

    if (deltaVelocity.getY() > 0) {
        display.fillRect(215, ceil(getPosition()->getY()), 54, ceil(deltaVelocity.getIntY()) + 1, TFT_BLACK);
    } else if (deltaVelocity.getY() < 0) {
        display.fillRect(215, ceil(getPosition()->getY() + 64 + deltaVelocity.getIntY()), 54, ceil(-deltaVelocity.getY()) + 1, TFT_BLACK);
    }
}

void Knight::setAnimation() 
{
    Animation& movementAnimation = getMovementAnimation();

    if (isOnGround()) {
        if (isRunning()) {
            isFacingRight() ? movementAnimation.setNewAnimation(knightRunRightBitmap, 0, 7, 100) : movementAnimation.setNewAnimation(knightRunLeftBitmap, 0, 7, 100);
        } else {
            isFacingRight() ? movementAnimation.setNewAnimation(knightIdleBitmap, 0, 2, 250) : movementAnimation.setNewAnimation(knightIdleBitmap, 1, 2, 250);
        }
    } else {
        isFacingRight() ? movementAnimation.setNewAnimation(knightJumpBitmap, 0, 0, -1) : movementAnimation.setNewAnimation(knightJumpBitmap, 1, 0, -1) ;
    }
}

void Knight::setAttackAnimation() 
{
    isFacingRight() ? getAttackAnimation().setNewAnimation(knightAttackBitmap, 0, 6, 4, 90) : getAttackAnimation().setNewAnimation(knightAttackBitmap, 1, 6, 4, 90);
}

void Knight::clearAfterImageAttackAnimation() 
{
    if (isFacingRight()) {
        DisplayManager::getDisplay().fillRect(215 + 54, getPosition()->getIntY() + 1, 10, 64, TFT_BLACK);
    }

    DisplayManager::getDisplay().fillRect(205, getPosition()->getIntY() + 1, 10, 64, TFT_BLACK);
}

void Knight::collisionWithCombatEntity(std::shared_ptr<CombatEntity> collisionCombatEntity, Rectangle::CollisionAxis axis) 
{

}