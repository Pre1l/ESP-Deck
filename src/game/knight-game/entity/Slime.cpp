#include "game/knight-game/entity/Slime.hpp"

#include "bitmap/knight-game/SlimeIdleBitmap.hpp"
#include "bitmap/knight-game/SlimeRunBitmap.hpp"

Slime::Slime(std::shared_ptr<Vector2D> position) 
: CombatEntity(position, 30, 16, 30, Vector2D(0, 0))
{
    type = Type::SLIME;

    stats.speedX = 0.05;
    stats.health = 50;
    stats.armor = 10;

    getMovementAnimation().setNewAnimation(slimeIdleBitmap, 0, 8, 150);
}

void Slime::setAnimation() 
{
    if (isOnGround() && isRunning()) {
        getMovementAnimation().setNewAnimation(slimeRunBitmap, 0, 7, 150);
        return;
    }

    getMovementAnimation().setNewAnimation(slimeIdleBitmap, 0, 8, 150);
}

void Slime::setAttackAnimation() 
{

}

void Slime::collisionWithCombatEntity(std::shared_ptr<CombatEntity> collisionCombatEntity, Rectangle::CollisionAxis axis) 
{

}