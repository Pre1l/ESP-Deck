#include "game/knight-game/entity/Slime.hpp"

#include "bitmap/knight-game/SlimeIdleBitmap.hpp"

Slime::Slime(std::shared_ptr<Vector2D> position) 
: CombatEntity(position, 30, 16, 30, Vector2D(0, 0))
{
    getMovementAnimation().setNewAnimation(slimeIdleBitmap, 0, 8, 150);
    startRunning(Slime::RIGHT);
}

void Slime::setAnimation() 
{

}