#include "game/knight-game/entity/Slime.hpp"

#include "bitmap/knight-game/SlimeIdleBitmap.hpp"
#include "bitmap/knight-game/SlimeRunBitmap.hpp"

Slime::Slime(std::shared_ptr<Vector2D> position) 
: CombatEntity(position, 30, 16, 30, Vector2D(0, 0))
{
    type = EntityType::SLIME;

    config.speedX = 0.05;

    getMovementAnimation().setNewAnimation(slimeIdleBitmap, 0, 8, 150);
    startRunning(Direction::RIGHT);
}

void Slime::setAnimation() 
{
    if (isOnGround() && isRunning()) {
        getMovementAnimation().setNewAnimation(slimeRunBitmap, 0, 7, 150);
        return;
    }

    getMovementAnimation().setNewAnimation(slimeIdleBitmap, 0, 8, 150);
}

void Slime::collisionWithCombatEntity(std::shared_ptr<CombatEntity> collisionCombatEntity, Rectangle::CollisionAxis axis) 
{
    
}